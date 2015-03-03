#include <pal.h>

#include <stdio.h>
#include "pal_base.h"
#include "pal_base_private.h"

/**
 *
 * Cleans up/finalizes the run time for device 'dev'. Should be called before
 * exiting the main program.
 *
 * @param dev   Device object desriptor (int)
 *
 * @return      Returns 0 if successful.
 *
 */

P_STATUS p_finalize(p_dev_t * dev)
{
    printf("Running p_finalize(%p)\n", dev);

    ((p_dev_ops_t*)dev->dev_ops)->fini(dev);

    return OK;
}
