#include <stdio.h>
#include <stdlib.h>

int my_div(int dividend, int divisor, double *quotient) {
    if (divisor == 0) {
        return 0;
    }
    *quotient = (double)dividend / divisor;
    return 1;
}

int main() {
    int dividend, divisor;
    double quotient;
    scanf("%d %d", &dividend, &divisor);
    if (!my_div(dividend, divisor, &quotient)) {
        printf("Divisor is 0\n");
    } else {
        printf("Quotient is %f\n", quotient);
    }
}
