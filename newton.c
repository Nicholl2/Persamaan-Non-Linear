#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_ITERATION 100
#define EPSILON 0.000001

int main() {
    double x[MAX_ITERATION], y[MAX_ITERATION];
    double u, v;         
    double dux, duy, dvx, dvy;  
    double det, deltaX, deltaY;

    int i = 0;
    x[0] = 1.5;
    y[0] = 3.5;

    printf("r\t   x\t\t   y\t\t  deltaX\t  deltaY\n");
    printf("---------------------------------------------------------\n");

    do {
        if (i >= MAX_ITERATION) break;

        u = x[i]*x[i] + x[i]*y[i] - 10;
        v = y[i] + 3*x[i]*y[i]*y[i] - 57;

        dux = 2*x[i] + y[i];
        duy = x[i];
        dvx = 3*y[i]*y[i];
        dvy = 1 + 6*x[i]*y[i];

        det = dux * dvy - duy * dvx;

        x[i+1] = x[i] - (u*dvy - v*duy) / det;
        y[i+1] = y[i] - (v*dux - u*dvx) / det;

        deltaX = fabs(x[i+1] - x[i]);
        deltaY = fabs(y[i+1] - y[i]);

        printf("%2d\t %.6f\t %.6f\t %.6f\t %.6f\n", i+1, x[i+1], y[i+1], deltaX, deltaY);
        i++;

    } while (deltaX > EPSILON || deltaY > EPSILON);

    if (i >= MAX_ITERATION)
        printf("Tidak konvergen dalam %d iterasi.\n", MAX_ITERATION);
    else
        printf("\nKonvergen dalam %d iterasi.\nHasil: x = %.6f, y = %.6f\n", i, x[i], y[i]);

    return 0;
}
