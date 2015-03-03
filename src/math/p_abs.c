#include <pal.h>

/**
 *
 * Compute the absolute value of the vector 'a'.
 *
 * @param a     Pointer to input vector
 *
 * @param c     Pointer to result vector
 *
 * @param n     Size of 'a' and 'c' vector.
 *
 * @return      None
 *
 */
void p_abs_f32(float *a, float *c, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        int casted = *(int*)(a);
        casted &= 0x7FFFFFFF;
        *c = *(float*)&casted;
        c++;
        a++;
    }
    //set first bit to 0
    //this sets sign = (+)
    //increment the pointers
}
