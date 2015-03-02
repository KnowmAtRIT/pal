#include <pal.h>

/**
 *
 * Calculate 'a' raised to the exponent 'b'
 *
 * @param a     Pointer to input vector
 *
 * @param b     Pointer to input vector
 *
 * @param c     Pointer to output vector
 *
 * @param n     Size of 'a' and 'c' vector.
 *
 * @return      None
 *
 */
#include <math.h>
void p_pow_f32(float *a, float *b, float *c, int n)
{

    int i;
    for (i = 0; i < n; i++)
        *c++ = powf(*a++, *b++);
}
