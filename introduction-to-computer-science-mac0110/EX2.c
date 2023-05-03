#include <stdio.h>

int main() {

    int n, x, maior;
 
    printf ("Digite  tamanho da sequencia:");
    scanf ("%d", &n);
    if (n<1) {
        printf ("Digite um numero valido!");
        main ();
        
    }

    printf ("\nDigite um numero:");
    scanf ("%d", &x);
    maior=x;

    while (n>1)
     {
        printf ("\nDigite um numero:");
        scanf ("%d", &x);
        if (x>maior) {
            maior=x;
        }
        n=n-1;

     }
     printf ("\nO maior numero da sequencia e %d", maior);
	
    return 0;
}