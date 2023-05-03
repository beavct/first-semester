#include <stdio.h>

int main () {
    int n, fat, mult;
    fat=2;
    
    printf ("\nDigite um numero:");
    scanf ("%d", &n);
        if (n<0){
            printf ("\nDigite um numero valido!");
            main ();
            }

    while (n>1) {

        mult=0;
        while (n%fat==0) {
            mult++;
            n=n/fat; 
            }

        if (mult!=0) {
            printf("\nFator %d multiplicidade %d", fat, mult); 
            }
        fat++; 
        }

  return 0;
}    