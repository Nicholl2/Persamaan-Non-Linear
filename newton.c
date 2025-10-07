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

// Turunan parsial f1 terhadap x: df1/dx = 2x + y
double df1_dx(double x, double y) {
    return 2.0*x + y;
}

// Turunan parsial f1 terhadap y: df1/dy = x
double df1_dy(double x, double y) {
    return x;
}

// Turunan parsial f2 terhadap x: df2/dx = 3y^2
double df2_dx(double x, double y) {
    return 3.0*y*y;
}

// Turunan parsial f2 terhadap y: df2/dy = 1 + 6xy
double df2_dy(double x, double y) {
    return 1.0 + 6.0*x*y;
}

// Fungsi untuk menghitung determinan matriks Jacobian 2x2
double determinant(double a11, double a12, double a21, double a22) {
    return a11*a22 - a12*a21;
}

int main() {
    const double x0 = 1.5;
    const double y0 = 3.5;
    
    double x_curr = x0;
    double y_curr = y0;
    double x_next, y_next;
    double deltaX, deltaY;
    int iteration = 0;
    
    // Variabel untuk matriks Jacobian dan invers
    double j11, j12, j21, j22;  // Elemen Jacobian
    double det;                  // Determinan
    double inv_j11, inv_j12, inv_j21, inv_j22;  // Elemen invers Jacobian
    double f1_val, f2_val;       // Nilai fungsi
    
    printf("================================================================================\n");
    printf("METODE NEWTON-RAPHSON untuk Sistem Persamaan Non-Linear\n");
    printf("================================================================================\n");
    printf("Sistem Persamaan:\n");
    printf("f1(x,y) = x^2 + xy - 10 = 0\n");
    printf("f2(x,y) = y + 3xy^2 - 57 = 0\n");
    printf("\nMatriks Jacobian J:\n");
    printf("J = | df1/dx  df1/dy |   | 2x+y    x    |\n");
    printf("    | df2/dx  df2/dy | = | 3y^2  1+6xy  |\n");
    printf("\nFormula Newton-Raphson:\n");
    printf("[x]     [x]         [f1(x,y)]\n");
    printf("[y]   = [y]  - J^-1 [f2(x,y)]\n");
    printf(" n+1     n\n");
    printf("\nNilai Awal: x0 = %.1f, y0 = %.1f\n", x0, y0);
    printf("Epsilon: %.6f\n", EPSILON);
    printf("================================================================================\n\n");
    
    printf("%-5s %-15s %-15s %-15s %-15s %-15s %-15s %-12s\n", 
           "Iter", "x", "y", "deltaX", "deltaY", "f1(x,y)", "f2(x,y)", "det(J)");
    printf("--------------------------------------------------------------------------------------------\n");
    
    // Iterasi awal
    printf("%-5d %-15.10f %-15.10f %-15s %-15s %-15.10f %-15.10f %-12s\n", 
           iteration, x_curr, y_curr, "-", "-", f1(x_curr, y_curr), f2(x_curr, y_curr), "-");
    
    do {
        if (iteration >= MAX_ITERATION) {
            printf("\nPeringatan: Mencapai iterasi maksimum!\n");
            break;
        }
        
        // Hitung nilai fungsi di titik saat ini
        f1_val = f1(x_curr, y_curr);
        f2_val = f2(x_curr, y_curr);
        
        // Hitung elemen matriks Jacobian
        j11 = df1_dx(x_curr, y_curr);  // df1/dx = 2x + y
        j12 = df1_dy(x_curr, y_curr);  // df1/dy = x
        j21 = df2_dx(x_curr, y_curr);  // df2/dx = 3y^2
        j22 = df2_dy(x_curr, y_curr);  // df2/dy = 1 + 6xy
        
        // Hitung determinan
        det = determinant(j11, j12, j21, j22);
        
        // Cek jika determinan terlalu kecil (singular matrix)
        if (fabs(det) < 1e-10) {
            printf("\nError: Matriks Jacobian singular (det ≈ 0)!\n");
            break;
        }
        
        // Hitung invers Jacobian
        // J^-1 = 1/det * | j22  -j12 |
        //                | -j21  j11 |
        inv_j11 =  j22 / det;
        inv_j12 = -j12 / det;
        inv_j21 = -j21 / det;
        inv_j22 =  j11 / det;
        
        // Update menggunakan Newton-Raphson
        // [x_new]   [x_curr]         [f1]
        // [y_new] = [y_curr] - J^-1 * [f2]
        x_next = x_curr - (inv_j11 * f1_val + inv_j12 * f2_val);
        y_next = y_curr - (inv_j21 * f1_val + inv_j22 * f2_val);
        
        // Hitung perubahan
        deltaX = fabs(x_next - x_curr);
        deltaY = fabs(y_next - y_curr);
        
        iteration++;
        
        printf("%-5d %-15.10f %-15.10f %-15.10f %-15.10f %-15.10f %-15.10f %-12.6f\n", 
               iteration, x_next, y_next, deltaX, deltaY, 
               f1(x_next, y_next), f2(x_next, y_next), det);
        
        // Update nilai untuk iterasi berikutnya
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
    
    printf("\n--- DETAIL PERHITUNGAN ITERASI TERAKHIR ---\n");
    printf("Matriks Jacobian pada solusi:\n");
    printf("J = | %10.6f  %10.6f |\n", df1_dx(x_curr, y_curr), df1_dy(x_curr, y_curr));
    printf("    | %10.6f  %10.6f |\n", df2_dx(x_curr, y_curr), df2_dy(x_curr, y_curr));
    printf("det(J) = %.6f\n", determinant(df1_dx(x_curr, y_curr), df1_dy(x_curr, y_curr),
                                          df2_dx(x_curr, y_curr), df2_dy(x_curr, y_curr)));
    
    return 0;
}
