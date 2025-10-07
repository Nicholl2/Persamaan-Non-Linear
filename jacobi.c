#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ITERATION 1000
#define EPSILON 0.000001

// Fungsi g1A: dari f1 = x^2 + xy - 10 = 0
// x^2 + xy = 10
// x = sqrt(10 - xy)
double g1A(double x, double y) {
    return sqrt(10 - x * y);
}

// Fungsi g2B: dari f2 = y + 3xy^2 - 57 = 0
// 3xy^2 = 57 - y
// y = sqrt((57 - y) / (3x))
double g2B(double x, double y) {
    return sqrt((57 - y) / (3 * x));
}

// Fungsi untuk menghitung f1 dan f2 (verifikasi)
double f1(double x, double y) {
    return x * x + x * y - 10;
}

double f2(double x, double y) {
    return y + 3 * x * y * y - 57;
}

int main() {
    const double x0 = 1.5;
    const double y0 = 3.5;

    double x_curr = x0;
    double y_curr = y0;
    double x_next, y_next;
    double deltaX, deltaY;
    int iteration = 0;

    printf("================================================================\n");
    printf("METODE JACOBI - Kombinasi g1A dan g2B (NIMx = 1)\n");
    printf("================================================================\n");
    printf("Sistem Persamaan:\n");
    printf("f1(x,y) = x^2 + xy - 10 = 0\n");
    printf("f2(x,y) = y + 3xy^2 - 57 = 0\n");
    printf("\nFungsi Iterasi:\n");
    printf("g1A: x = sqrt(10 - xy)\n");
    printf("g2B: y = sqrt((57 - y) / (3x))\n");
    printf("\nNilai Awal: x0 = %.1f, y0 = %.1f\n", x0, y0);
    printf("Epsilon: %.6f\n", EPSILON);
    printf("================================================================\n\n");

    printf("%-5s %-15s %-15s %-15s %-15s %-15s %-15s\n",
           "Iter", "x", "y", "deltaX", "deltaY", "f1(x,y)", "f2(x,y)");
    printf("--------------------------------------------------------------------------------\n");

    // Iterasi awal
    printf("%-5d %-15.10f %-15.10f %-15s %-15s %-15.10f %-15.10f\n",
           iteration, x_curr, y_curr, "-", "-", f1(x_curr, y_curr), f2(x_curr, y_curr));

    do {
        if (iteration >= MAX_ITERATION) {
            printf("\nPeringatan: Mencapai iterasi maksimum!\n");
            break;
        }

        // Jacobi: gunakan nilai lama untuk menghitung x_next dan y_next
        x_next = g1A(x_curr, y_curr);
        y_next = g2B(x_curr, y_curr);

        // Cek jika hasil tak valid (akar negatif)
        if (isnan(x_next) || isnan(y_next)) {
            printf("\nPeringatan: Iterasi menghasilkan nilai tidak valid (NaN)!\n");
            break;
        }

        // Hitung perubahan
        deltaX = fabs(x_next - x_curr);
        deltaY = fabs(y_next - y_curr);

        iteration++;

        printf("%-5d %-15.10f %-15.10f %-15.10f %-15.10f %-15.10f %-15.10f\n",
               iteration, x_next, y_next, deltaX, deltaY, f1(x_next, y_next), f2(x_next, y_next));

        // Update untuk iterasi berikutnya
        x_curr = x_next;
        y_curr = y_next;

    } while (deltaX > EPSILON || deltaY > EPSILON);

    printf("================================================================================\n");
    printf("\nSOLUSI DITEMUKAN:\n");
    printf("Iterasi: %d\n", iteration);
    printf("x = %.10f\n", x_curr);
    printf("y = %.10f\n", y_curr);
    printf("\nVerifikasi:\n");
    printf("f1(x,y) = %.10e (harus mendekati 0)\n", f1(x_curr, y_curr));
    printf("f2(x,y) = %.10e (harus mendekati 0)\n", f2(x_curr, y_curr));
    printf("================================================================================\n");

    return 0;
}
