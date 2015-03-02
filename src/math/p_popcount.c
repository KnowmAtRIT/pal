#include <pal.h>

/**
 *
 * Counts the number of bits set in 'a'.
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
void p_popcount_u32(unsigned int *a, unsigned int *c, int n)
{
    int i = 0;
    int j = 0;

    for(i=0; i < n; i++)
    {
        *c = 0;

        for(j=0; j < sizeof(unsigned int); j++)
        {
            *c += *a % 2; // grab our relevant bit
            *a >>= 1; // shift away
        }

        a++;
        c++;
    }
}
