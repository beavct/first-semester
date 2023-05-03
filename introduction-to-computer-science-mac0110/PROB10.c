#include <stdio.h>

int main () {
	int n, soma, x;

	printf ("\nDigite um numero:");
	scanf ("%d", &n);
	soma=0;

	while (n>0){
		soma=soma+n%10;
		n=n/10;
	}
	printf ("\nA soma %d", soma);
	return 0;
}
	

