#include <pal.h>

/**
 *
 * Element wise multiply accumulate: c += a * b'
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
void p_mac_f32(float *a, float *b, float *c, int n)
{
    int i;
    *c = 0.0f;
    for (i = 0; i < n; i++)
        *c += *a++ * *b++;
}
