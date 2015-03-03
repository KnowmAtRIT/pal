#include <pal.h>
#include <stdio.h>
/**
 *
 * Frees up resources occupied by 'mem'.
 *
 * @param mem Memory object descriptor (int)
 *
 * @return    Returns 0 if successful.
 *
 */

P_STATUS p_free(p_mem_t *mem)
{
    printf("Running p_free(%p)\n", mem);
    return OK;
}
