#include <pal.h>

/**
 *
 * Calculates the median value of input vector 'a'.
 *
 * @param a     Pointer to input vector
 *
 * @param c     Pointer to output scalar
 *
 * @param n     Size of 'a' vector.
 *
 * @return      None
 *
 */
void p_median_f32(float *a, float *c, int n) {
    float temp[n];
    p_sort_f32( a , temp, n);
    *c = temp[n/2 + 1];
}
