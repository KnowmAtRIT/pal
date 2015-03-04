#include <pal.h>

/**
 * A Sobel 3x3 convolution filter (m) with the Sobel operators defined as:
 *
 *       | -1  0  1 |
 * Gx =  | -2  0  2 | * 1/8
 *       | -1  0  1 |
 *
 *       | -1 -2 -1 |
 * Gy =  |  0  0  0 | * 1/8
 *       |  1  2  1 |
 *
 * G = sqrt (Gx^2 + Gy^2)
 *
 * Gradient Direction (theta) = atan2(Gy,Gx)
 *
 * @param x    Pointer to input image, a 2D array of size 'rows' x 'cols'
 *
 * @param rows Number of rows in input image
 *
 * @param cols Number of columns in input image
 *
 * @param r    Pointer to output image
 *
 */
#include <math.h>

void p_sobel3x3_f32(float *x, int rows, int cols, float *r)
{

    int ia, ja;
    float Dx, Dy;
    float *px, *pr;

    px = x;
    pr = r;

    for (ia = 1; ia <= (rows - 2); ia++) {
        for (ja = 1; ja <= (cols - 2); ja++) {

            // Nasty stuff..
            Dx = Dy = 0;
            Dx -= (*px);
            Dy -= (*px++);
            Dy -= (*px++) * 2;
            Dx += (*px);
            Dy -= (*px++);
            px += cols - 3;
            Dx -= (*px) * 2;
            px++;
            px++;
            Dx += (*px) * 2;
            px++;
            px += cols - 3;
            Dx -= (*px);
            Dy += (*px++);
            Dy += (*px++) * 2;
            Dx += (*px);
            Dy += (*px++);
            px += cols - 3;

            *pr = sqrtf(Dx * Dx + Dy * Dy) *
                  M_DIV8; // optimize: get rid of sqrt
            //*pr = (fabs(Dx) + fabs(Dy)) * reciprocal[8]; //(slightly faster
            // alternative)
            px += 1 - 3 * cols; // advance mask matrix in one column, get rid of
                                // integer multiply?
            pr++;
        }
        px = px + 2; // at the last column in a row, advance pointer to the
                     // beginning of next row.
    }
    return;
}
