#include <pal.h>

/**
 *
 * Calculates the square root of the input vector 'a'.
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
void p_sqrt_f32(float *a, float *c, int n)
{

    int i;
    for (i = 0; i < n; i++)
        *c++ = sqrtf(*a++);
}
