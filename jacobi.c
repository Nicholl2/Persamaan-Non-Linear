#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ITERATION 100
#define EPSILON 0.000001

int main() {
    const double x0 = 1.5;
    const double y0 = 3.5;

    double x[MAX_ITERATION];
    double y[MAX_ITERATION];
    double deltaX = 0, deltaY = 0;
    int i = 0;

    x[0] = x0;
    y[0] = y0;

    printf("---------------------------------------------------------\n");
    printf("r\t     x\t\t     y\t\t  deltaX\t  deltaY\n");
    printf("---------------------------------------------------------\n");

    do {
        if (i >= MAX_ITERATION) break;

        // 🔎 cek dulu biar gak ambil akar negatif
        if ((10 - x[i]*y[i]) < 0 || (57 - y[i]) / (3 * x[i]) < 0) {
            printf("Iterasi ke-%d: domain error (akar negatif)\n", i+1);
            break;
        }

        // Jacobi: pakai nilai lama untuk keduanya
        double x_next = sqrt(10 - x[i] * y[i]);
        double y_next = sqrt((57 - y[i]) / (3 * x[i]));

        deltaX = fabs(x_next - x[i]);
        deltaY = fabs(y_next - y[i]);

        if (i < 100)
            printf("%2d\t %.6f\t %.6f\t %.6f\t %.6f\n",
                   i + 1, x_next, y_next, deltaX, deltaY);

        i++;
        x[i] = x_next;
        y[i] = y_next;

    } while (deltaX > EPSILON || deltaY > EPSILON);

    if (i >= MAX_ITERATION)
        printf("Tidak konvergen dalam %d iterasi.\n", MAX_ITERATION);
    else
        printf("\nKonvergen dalam %d iterasi.\nHasil: x = %.6f, y = %.6f\n",
               i, x[i], y[i]);

    return 0;
}
