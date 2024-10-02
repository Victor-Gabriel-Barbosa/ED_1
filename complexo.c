#include <stdio.h>
#include <complex.h>

int main() {
    // Declara um número complexo
    double complex z1 = 1.0 + 2.0 * I; // 1 + 2i
    double complex z2 = 3.0 + 4.0 * I; // 3 + 4i

    // Adição
    double complex sum = z1 + z2;
    printf("Soma: %.1f + %.1fi\n", creal(sum), cimag(sum));

    // Multiplicação
    double complex product = z1 * z2;
    printf("Produto: %.1f + %.1fi\n", creal(product), cimag(product));

    // Módulo
    double magnitude = cabs(z1);
    printf("Magnitude de z1: %.2f\n", magnitude);

    // Exponencial
    double complex exp_z1 = cexp(z1);
    printf("Exponencial de z1: %.1f + %.1fi\n", creal(exp_z1), cimag(exp_z1));

    return 0;
}
