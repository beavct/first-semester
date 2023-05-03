#include <stdio.h>

int main (){
    double x, eul = 0, eps, num, den, i;

    printf ("Digite o valor de x e de eps (eps > 0):\n");
    scanf ("%lf %lf", &x, &eps);

    num = x, den = 1, i = 1;

    while ( num/ den >= eps || num / den <= -eps) {
        eul = eul + (num / den);
        num = num * x;
        den = den * i;
        i++;
    }

    eul = eul + (num / den);
    printf ("O aproximacao e %lf", eul);
    return 0;
}