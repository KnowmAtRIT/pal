#include <pal.h>

/**
 *
 * Calculates the dot product between vectors 'a' and 'b', producing
 * a scalar result 'c'.
 *
 * @param a     Pointer to input vector
 *
 * @param b     Pointer to input vector
 *
 * @param c     Pointer to output scalar
 *
 * @param n     Size of 'a', 'b'
 *
 * @return      None
 *
 */
void p_dot_f32(float *a, float *b, float *c, int n)
{
    int i;
    *c = 0.0f;
    for (i = 0; i < n; i++)
        *c += *a++ * *b++;
}
