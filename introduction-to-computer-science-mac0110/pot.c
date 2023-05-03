#include <stdio.h>

int main (){
    int num, x, k, i;

    printf ("Digite o valor de x e de k:");
    scanf ("%d %d", &x, &k);

    num = x;

    for (i = 2; i <= k; i++) {
        num = num * x;
    }

    printf ("%d", num);

    return 0;

}