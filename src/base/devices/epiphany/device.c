#include <string.h>
#include "config.h"
#include "dev_epiphany.h"
#include "ctrl.h"
#include "pal_base.h"
#include "../../pal_base_private.h"
#include <e-hal.h>
#include <e-loader.h>

static P_STATUS dev_init( p_dev_t *dev, int flags)
{
    int err;
    struct epiphany_dev_data *data;
    struct epiphany_ctrl_mem ctrl = { .status = { 0 } };

    /* Be idempotent if already initialized. It might be a better idea to
     * return EBUSY instead */
    if (dev->dev_data)
        return OK;


    err = e_init(NULL);
    if (err)
        return ERROR_IO;
    err = e_reset_system();
    if (err)
        return ERROR_IO;

    data = malloc(sizeof(*data));
    if (!data)
        return ERROR_NO_MEMORY;

    memset(data, 0, sizeof(*data));

    /* Open entire device */
    err = e_open(&data->dev, 0, 0, 4, 4);
    if (err) {
        free(data);
        return ERROR_IO;
    }
    err = e_alloc(&data->ctrl, CTRL_MEM_OFFSET, CTRL_MEM_SIZE);
    if (err) {
	free(data);
        return ERROR_NO_MEMORY;
    }
    e_write(&data->ctrl, 0, 0, 0, &ctrl, sizeof(ctrl));

    data->opened = 1;

    dev->dev_data = (void *) data;

    return E_OK;

}

static void dev_fini(struct dev *dev)
{
    struct epiphany_dev_data *data =
        (struct epiphany_dev_data *) dev->dev_data;

    if (!data)
        return;

    if (data->opened)
        e_close(&data->dev);

    e_finalize();

    free(dev->dev_data);
    dev->dev_data = NULL;
}

static int dev_query(struct dev *dev, P_PROP property)
{
    if (!dev)
        return -EINVAL;

    switch (property) {
    case TYPE:
        return P_DEV.EPIPHANY;
    case NODES:
        return 16;
    case TOPOLOGY:
        return 2;
    case ROWS:
        return 4;
    case COLS:
        return 4;
    case PLANES:
        return 4;
    case CHIPROWS:
        return 4;
    case CHIPCOLS:
        return 4;
    case SIMD:
        return 1;
    case MEMSIZE:
        return 32768;
    case MEMBASE:
        return 0x80800000;
    case VERSION:
        return 0xdeadbeef;
    case MEMARCH:
    case WHOAMI:
        return -ENOSYS;
    }
    return -EINVAL;
}

static P_STATUS dev_open(struct dev *dev, struct team *team, int start,
        int count )
{
    struct epiphany_dev_data *data =
        (struct epiphany_dev_data *) dev->dev_data;

    /* Only support opening entire chip for now */
    if (start != 0 || count != 16)
        return ERROR_INVALID;

    /* Open was done in init */
    if (!data->opened)
        return ERROR_BADF;

    team->dev = dev;

    return OK;
}

static int dev_run(struct dev *dev, struct team *team, struct prog *prog,
        int start, int size, int argn, char *args[], int flags)
{
    int err;
    int i;
    const uint32_t scheduled = STATUS_SCHEDULED;
    struct epiphany_dev_data *data = dev->dev_data;

    if (start < 0 || size <= 0)
        return -EINVAL;

    /* Assume we have entire chip for now */
    if (16 < start + size)
        return -EINVAL;

    if (!data || !data->opened)
        return -EBADF;

    /* Load */
    for (i = start; i < start + size; i++) {
        err = e_load(prog->path, &data->dev, i / 4, i % 4, E_FALSE);
        if (err)
            return -EIO;
    }
    /* Mark as scheduled */
    for (i = start; i < start + size; i++) {
        e_write(&data->ctrl, 0, 0,
                offsetof(struct epiphany_ctrl_mem, status) + i * sizeof(uint32_t),
                &scheduled, sizeof(scheduled));
    }
    /* Kick off */
    for (i = start; i < start + size; i++) {
        err = e_start(&data->dev, i / 4, i % 4);
        if (err)
            return -EIO;
    }

    return 0;

}


static int dev_wait(struct dev *dev, struct team *team)
{
    unsigned i;
    bool need_wait = true;
    struct epiphany_ctrl_mem ctrl;
    struct epiphany_dev_data *data =
        (struct epiphany_dev_data *) dev->dev_data;

    while (true) {
        need_wait = false;
        e_read(&data->ctrl, 0, 0, 0, &ctrl, sizeof(ctrl));
        for (i = 0; i < 16; i++) {
            switch (ctrl.status[i]) {
            case STATUS_SCHEDULED:
                /* TODO: Time out if same proc is in scheduled state too long.
                 * If program does not start immediately something has gone
                 * wrong.
                 */
            case STATUS_RUNNING:
                need_wait = true;
                break;
            case STATUS_NONE:
            case STATUS_DONE:
            default:
                continue;
            }
        }
        if (!need_wait)
            break;

        /* Don't burn CPU. Need HW/Kernel support for blocking wait */
        usleep(1000);
    }

    return 0;

}

struct dev_ops __pal_dev_epiphany_ops = {
    .init = dev_init,
    .fini = dev_fini,
    .query = dev_query,
    .open = dev_open,
    .run = dev_run,
    .wait = dev_wait
};

