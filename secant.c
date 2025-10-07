#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ITERATION 1000
#define EPSILON 0.000001

// Fungsi f1(x,y) = x^2 + xy - 10
double f1(double x, double y) {
    return x*x + x*y - 10.0;
}

// Fungsi f2(x,y) = y + 3xy^2 - 57
double f2(double x, double y) {
    return y + 3.0*x*y*y - 57.0;
}

int main() {
    // Dua titik awal untuk metode Secant
    const double x0 = 1.5;
    const double y0 = 3.5;
    
    // Titik kedua (sedikit berbeda dari titik pertama)
    const double x1 = 1.6;
    const double y1 = 3.6;
    
    // Variabel untuk iterasi
    double x_prev = x0;
    double y_prev = y0;
    double x_curr = x1;
    double y_curr = y1;
    double x_next, y_next;
    
    double f1_prev, f1_curr, f2_prev, f2_curr;
    double deltaX, deltaY;
    
    // Turunan numerik (pendekatan)
    double df1_dx, df2_dy;
    
    int iteration = 1;  // Mulai dari 1 karena sudah ada 2 titik awal
    
    printf("================================================================================\n");
    printf("METODE SECANT untuk Sistem Persamaan Non-Linear\n");
    printf("================================================================================\n");
    printf("Sistem Persamaan:\n");
    printf("f1(x,y) = x^2 + xy - 10 = 0\n");
    printf("f2(x,y) = y + 3xy^2 - 57 = 0\n");
    printf("\nFormula Secant (pendekatan turunan secara numerik):\n");
    printf("x[n+1] = x[n] - f1(x[n],y[n]) * (x[n]-x[n-1])/(f1(x[n],y[n])-f1(x[n-1],y[n-1]))\n");
    printf("y[n+1] = y[n] - f2(x[n],y[n]) * (y[n]-y[n-1])/(f2(x[n],y[n])-f2(x[n-1],y[n-1]))\n");
    printf("\nDua Titik Awal:\n");
    printf("Titik 0: x0 = %.1f, y0 = %.1f\n", x0, y0);
    printf("Titik 1: x1 = %.1f, y1 = %.1f\n", x1, y1);
    printf("Epsilon: %.6f\n", EPSILON);
    printf("================================================================================\n\n");
    
    printf("%-5s %-15s %-15s %-15s %-15s %-15s %-15s\n", 
           "Iter", "x", "y", "deltaX", "deltaY", "f1(x,y)", "f2(x,y)");
    printf("--------------------------------------------------------------------------------------------\n");
    
    // Tampilkan titik awal
    printf("%-5d %-15.10f %-15.10f %-15s %-15s %-15.10f %-15.10f\n", 
           0, x_prev, y_prev, "-", "-", f1(x_prev, y_prev), f2(x_prev, y_prev));
    printf("%-5d %-15.10f %-15.10f %-15s %-15s %-15.10f %-15.10f\n", 
           1, x_curr, y_curr, "-", "-", f1(x_curr, y_curr), f2(x_curr, y_curr));
    
    do {
        if (iteration >= MAX_ITERATION) {
            printf("\nPeringatan: Mencapai iterasi maksimum!\n");
            break;
        }
        
        // Hitung nilai fungsi di titik sebelumnya dan saat ini
        f1_prev = f1(x_prev, y_prev);
        f1_curr = f1(x_curr, y_curr);
        f2_prev = f2(x_prev, y_prev);
        f2_curr = f2(x_curr, y_curr);
        
        // Cek pembagian dengan nol
        if (fabs(f1_curr - f1_prev) < 1e-12) {
            printf("\nError: f1(x[n],y[n]) - f1(x[n-1],y[n-1]) ≈ 0 (pembagian dengan nol)!\n");
            break;
        }
        if (fabs(f2_curr - f2_prev) < 1e-12) {
            printf("\nError: f2(x[n],y[n]) - f2(x[n-1],y[n-1]) ≈ 0 (pembagian dengan nol)!\n");
            break;
        }
        
        // Hitung turunan numerik menggunakan metode secant
        // df1/dx ≈ (f1(x[n],y[n]) - f1(x[n-1],y[n-1])) / (x[n] - x[n-1])
        // df2/dy ≈ (f2(x[n],y[n]) - f2(x[n-1],y[n-1])) / (y[n] - y[n-1])
        df1_dx = (f1_curr - f1_prev) / (x_curr - x_prev);
        df2_dy = (f2_curr - f2_prev) / (y_curr - y_prev);
        
        // Update menggunakan metode Secant
        // x[n+1] = x[n] - f1(x[n],y[n]) / df1_dx
        // y[n+1] = y[n] - f2(x[n],y[n]) / df2_dy
        x_next = x_curr - f1_curr / df1_dx;
        y_next = y_curr - f2_curr / df2_dy;
        
        // Hitung perubahan
        deltaX = fabs(x_next - x_curr);
        deltaY = fabs(y_next - y_curr);
        
        iteration++;
        
        printf("%-5d %-15.10f %-15.10f %-15.10f %-15.10f %-15.10f %-15.10f\n", 
               iteration, x_next, y_next, deltaX, deltaY, 
               f1(x_next, y_next), f2(x_next, y_next));
        
        // Update nilai untuk iterasi berikutnya
        x_prev = x_curr;
        y_prev = y_curr;
        x_curr = x_next;
        y_curr = y_next;
        
    } while (deltaX > EPSILON || deltaY > EPSILON);
    
    printf("============================================================================================\n");
    printf("\nSOLUSI DITEMUKAN:\n");
    printf("Iterasi: %d\n", iteration);
    printf("x = %.10f\n", x_curr);
    printf("y = %.10f\n", y_curr);
    printf("\nVerifikasi:\n");
    printf("f1(x,y) = %.10e (harus mendekati 0)\n", f1(x_curr, y_curr));
    printf("f2(x,y) = %.10e (harus mendekati 0)\n", f2(x_curr, y_curr));
    printf("============================================================================================\n");
    
    return 0;
}
