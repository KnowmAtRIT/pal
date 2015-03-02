#include <pal.h>

/**
 *
 * Calculates the cube root of the input vector 'a'.
 *
 * @param a     Pointer to input vector
 *
 * @param c     Pointer to output vector
 *
 * @param n     Size of 'a' and 'c' vector.
 *
 * @return      None
 *
 */
#include <math.h>
void p_cbrt_f32(float *a, float *c, int n)
{
    int i;
    for (i = 0; i < n; i++)
        *c++ = cbrtf(*a++);
}
