#include <pal.h>
#include <float.h>

/**
 *
 * Finds the minimum value in vector 'a'. Returns the min value and the
 * greatest index of the minimum value. If n is 0, index will be -1 and c will
 * be the value of FLT_MAX.
 *
 * @param      a      Pointer to input vector
 *
 * @param[out] c      Pointer to output scalar
 *
 * @param[out] index  Pointer to return index of max
 *
 * @param n           Size of 'a' vector.
 *
 * @return            None
 *
 */
void p_min_f32(float *a, float *c, int *index, int n)
{
    int i;
    *index = -1;

    *c = FLT_MAX;
    for (i = 0; i < n; i++) {
        if (*a <= *c) {
            *index = i;
            *c = *a;
        }
        a++;
    }
}
