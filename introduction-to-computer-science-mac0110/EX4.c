#include <stdio.h>

int main () {
    int num, aux, rev;

    printf ("Digite um numero (n=>10):");
    scanf ("%d", &num);

    aux=num;
    rev=0;

    while (aux>0) {
        rev=rev*10+aux%10;
        aux=aux/10;
    }

    if (rev==num) {
        printf ("O numero %d e palindromo.", num);
    }
    else {
        printf ("O numero %d nao e palindromo.", num);
    }
    return 0;
}