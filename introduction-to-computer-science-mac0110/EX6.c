#include <stdio.h>

int contadigitos ();
int main (){
    int numA, numB, d, permutacao = 1;

    printf ("Digite o numero A e o numero B (sem conter o digito 0)\n");
    scanf ("%d %d", &numA, &numB);

    for (d = 1; d <= 9; d++) {
        if (contadigitos(numA, d) != contadigitos(numB, d)){
            permutacao = 0;
        }
    }

    if (permutacao) {
        printf ("%d e permutacao de %d", numA, numB);
    }
    else {
        printf ("%d nao e permutacao de %d", numA, numB);
    }
    return 0;
}

int contadigitos (int n, int d) {
    int conta = 0, resto;

    while (n != 0){
        resto = n % 10;
        n = n / 10;

        if (resto == d) {
            conta++;
        }
    }
    return conta;
}