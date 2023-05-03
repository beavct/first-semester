#include <stdio.h>
#include <stdlib.h>

int main () {
    int num;
    int depuracao, jogos, vitorias, acertos;
    int escolha, chute, tentativas;
    int dig1, dig2, dig3;
    int cDig1, cDig2, cDig3;

    num=rand()%1000;
    dig1=num/100;
    dig2=(num-dig1)/10;
    dig3=num%10;

    jogos=0;
    vitorias=0;
    cDig1=0, cDig2=0, cDig3=0;
    depuracao=0;

    while ( escolha != 3) {
        
        printf ("Bem-vindo ao jogo da forca!!\n"
                "----------------------------\n");

        if (depuracao == 0 ) {
            printf ("[Depuracao = DESLIGADO | Jogos jogados = %d]\n", jogos);
        }
        else {
            printf ("[Depuracao = LIGADO | Jogos jogados = %d]\n", jogos);
        }
        
        printf ("1. Continuar a jogar.\n"
                "2. Alterar modo depuracao e continuar a jogar.\n"
                "3. Parar.\n"
                "Escolha uma opcao:\n");
        scanf ("%d", &escolha);

        if (escolha == 2) {
            if (depuracao == 1) {
                depuracao=0;
            }
            else {
                depuracao=1;               
            }           
        }
        tentativas=6;
        acertos=0;

        if (escolha != 3) {
            do {
                    
                if (depuracao == 1) {
                    printf ("O numero a ser adivinhado e: %d\n", num);
                } 

                printf ("Restam %d tentativas\n"
                        "Sua proxima tentativa (digito de 0 a 9):\n", tentativas);
                scanf ("%d", &chute);

                if (chute == dig1) {
                    cDig1=1;
                    acertos++;
                }
                if (chute == dig2) {
                    cDig2=1;
                    acertos++;
                }
                if (chute == dig3) {
                    cDig3=1;
                    acertos++;
                }
                tentativas--;
                    
                if (cDig1) {
                    printf ("Voce ja acertou os seguintes digitos: %d", dig1);
                }
                else {
                    printf ("Voce ja acertou os seguintes digitos: -");
                }

                if (cDig2){
                    printf ("%d", dig2);
                }
                else {
                    printf ("-");
                }

                if (cDig3) {
                    printf ("%d\n", dig3);
                }
                else {
                    printf ("-\n");
                }

            } while ( tentativas>0 && acertos<3 && escolha != 3 );

            if (acertos == 3) {
                printf ("Voce VENCEU!!\n");
                vitorias++;
            }
            else {
                printf ("Voce PERDEU!!\n");
            }
            jogos++;
            tentativas=6;
            acertos=0;
            cDig1=0, cDig2=0, cDig3=0;
        }
            

    }
    printf ("Voce jogou %d jogos e ganhou %d", jogos, vitorias);    
    return 0;
}