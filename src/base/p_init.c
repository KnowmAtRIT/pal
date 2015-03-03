#include <pal.h>

/**
 *
 * Initalizes the loader run time system information based on the device type
 * and flag arguments provided. All necesssary system information is aggregated
 * in the an object 'dev' for use by other pal functions. An example of the
 * minimum amount of information needed includes the number of processors in
 * the system and an address map/scheme.
 *
 * @param type  The type of worker device being used
 *
 *        EPIPHANY - An array of RISC processors with distributed shared memory
 *        FPGA     - A set of FPGA accelerators supported by a host processor
 *        SMP      - Multiple core shared memory processor system
 *        GPU      - GPUs supported by the OpenCL runtime
 *        GRID     - A distributed system of processors with IP addresses
 *                   Can fall back to the local host as well ("batch")
 *
 * @param flags Bitmask field indicating runtime options
 *
 * @return      Returns a reference to the device object.
 *              A negative value indicates error.
 */

#include <stdio.h>
#include "pal_base.h"
#include "pal_base_private.h"

P_STATUS p_init(P_DEV type, int flags, p_dev_t * device)
{
    struct dev *dev = NULL;

    if (type < P_DEV_FIRST || P_DEV_LAST < type)
        return ERROR_INVALID;

    dev = &__pal_global.devs[type];

    /* Check if compiled in */
    if (!dev->dev_ops)
        return ERROR_NO_SYSTEM;
    device = dev->dev_ops->init(dev,flags);

    return OK;
}
