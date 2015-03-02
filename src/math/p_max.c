#include <pal.h>
#include <float.h>
/**
 *
 * Finds the maximum value in vector 'a'. Returns the index of the max
 *
 * @param a           Pointer to input vector
 *
 * @param c           Pointer to output scalar
 *
 * @param[out] index  Pointer to return index of max
 *
 * @param n      Size of 'a' vector.
 *
 * @return       None
 *
 */
void p_max_f32(float *a, float *c, int *index, int n)
{
    int i;
    *c = FLT_MIN;
    *index = -1;
    for (i = 0; i < n; i++) {
        if (*a > *c) {
            *index = i;
            *c = *a;
        }
	a++;
    }
}
