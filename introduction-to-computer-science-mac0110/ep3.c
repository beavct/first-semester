#include <stdio.h>
#include <stdlib.h>
#define MAX 256

int *load_image_from_file(char *filename, int *w, int *h);
void save_image_to_file(char *filename, int *I, int w, int h);
int *invert_image(int *I, int w, int h);
int *label_components(int *I, int w, int h, int *ncc);
int *filter_image(int *I, int w, int h, int d, int tipo);
int *contorno_img (int *I, int w, int h);
int *binarize(int *I, int w, int h, int t);

/*Revisar main depois para ver se não tem coisas redundantes*/

int main () {
    int *E = NULL /*imagem-entrada*/, *T = NULL /*imagem-transformada*/;
    int largura, altura, tamanho, filtro, limiar, ncomponentes;
    char filename[MAX], escolha;
    int rodando = 1;

    while (rodando) {
        printf ("----------------------------------------------\n");
        printf ("Escolha uma opcao:\n");
        printf ("Q. Quit\n");
        printf ("L. Ler um arquivo\n");
        printf ("S Salvar a imagem em arquivo\n");
        printf ("M. Manter a imagem-entrada anterior\n\n");
        printf ("B. Binarizar a imagem-entrada\n");
        printf ("C. Calcular Contorno da imagem-entrada\n");
        printf ("F. Filtrar a imagem-entrada\n");
        printf ("I. Inverter a imagem-entrada\n");
        printf ("R. Rotular os componentes conexos\n");
        scanf ("%c", &escolha);  

        if (escolha == 'L' || escolha == 'l') {
            E = NULL; T = NULL;
            load_image_from_file (filename, &largura, &altura);
        }
        if (escolha == 'M' || escolha == 'm') {
            if (E == NULL) {
                printf ("Nao ha imagem-entrada alocada\n");
            }
            if (T != NULL) {
                free (T); T = NULL;
            }
        }
        if (escolha == 'S' || escolha == 's') {
            if (E == NULL && T == NULL) printf ("Nao ha imagem de entrada alocada\n");      
            if (E != NULL && T == NULL) {
                save_image_to_file (filename, E, largura, altura);
            }
            else /*E != NULL && T != NULL*/ save_image_to_file (filename, T, largura, altura);

        }  
        if (escolha == 'B' || escolha == 'b') {
            printf ("Digite o limiar:\n");
            scanf ("%d", &limiar);
            if (E == NULL && T == NULL) printf ("Nao ha imagem de entrada alocada.\n");
            if (E != NULL && T == NULL) T = binarize (E, largura, altura, limiar);
            if (E != NULL && T != NULL) {
                E = T;
                T = binarize (E, largura, altura, limiar);
            }
        }
        if (escolha == 'C' || escolha == 'c') {
            if (E == NULL && T ==  NULL) printf ("Nao ha imagem de entrada alocada\n");
            if (E != NULL && T == NULL) {

            }
            if (E != NULL && T != NULL) {
                E = T;
                /*chamada da função*/
            }

        }
        if (escolha == 'F' || escolha == 'f') {
            if (E == NULL && T ==  NULL) {
                printf ("Nao ha imagem de entrada alocada\n");
                return 0; 
            }
            printf ("Digite o tipo do filtro:\n");
            scanf ("%d", &filtro);
            printf ("Digite o tamanho do filtro (numero impar):\n");
            scanf ("%d", &tamanho);
            if (E != NULL && T == NULL) filter_image (E, largura, altura, tamanho, filtro);
            if (E != NULL && T != NULL) {
                E = T;
                filter_image (E, largura, altura, tamanho, filtro);
            }

        }
        if (escolha == 'I' || escolha == 'i') {
            if (E == NULL) printf ("Nao ha imagem de entrada alocada.\n");
            if (E != NULL && T == NULL) T = invert_image (E, largura, altura);
            if (E != NULL && T != NULL) {
                E = T;
                T = invert_image (E, largura, altura);
            }
        }
        if (escolha == 'R' || escolha == 'r') {
            if (E == NULL && T ==  NULL) printf ("Nao ha imagem de entrada alocada\n");
            if (E != NULL && T == NULL) label_components (E, largura, altura, &ncomponentes);
            if (E != NULL && T != NULL) {
                E = T;
                label_components (E, largura, altura, &ncomponentes);
            }

        }
        if (escolha == 'Q' || escolha == 'q') {
            if (E == NULL) {
                free (E); E = NULL;
            }
            if (T == NULL) {
                free (T); T = NULL;
            }
            rodando = 0;
        }
    }


    return 0;
}

int *load_image_from_file (char *filename, int *w, int *h) {
    FILE *arq;
    int *V;
    int i;
    char line1[10], line2[10];

    printf ("Digite o nome do arquivo de entrada:\n");
    scanf ("%c", filename);

    arq = fopen (filename, "r");
    fscanf (arq, "%[^\n]\n", line1);
    fscanf (arq, "%d %d", &*w, &*h);
    fscanf (arq, "%[^\n]\n", line2);         
   
    V = malloc (sizeof(int) * *w * *h);

    for (i = 0; i < (*w * *h); i++) {
        fscanf (arq, "%d", &V[i]);
    }
    fclose (arq);
    return V;
}

void save_image_to_file(char *filename, int *I, int w, int h) {
    FILE *arq;
    int i, j; 

    printf ("Digite o nome do arquivo de saida:\n");
    scanf ("%c", filename);

    arq = fopen (filename, "w");
    fprintf (arq, "P2\n");
    fprintf (arq, "%d %d\n", w, h);
    fprintf (arq, "255\n");

    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            fprintf (arq, "%d", I[(i * w) + j]);
        }
    }
    fclose (arq);
}

int *invert_image(int *I, int w, int h) {
    int *R, i, j;

    R = malloc (sizeof(int) * w * h);

    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            R[(i * w) + j] = 255 - I[(i * w) + j];
        }
    }
    return R;
}

int *label_components(int *I, int w, int h, int *ncc) {

}

int *contorno_img (int *I, int w, int h) {
    /*Usa a função filtro, d=3 e tipo do filtro=1, depois faz *E - *F*/ 
    int *R, *F;
    int i, j;

    R = malloc (sizeof(int) * w * h);
    F = malloc (sizeof(int) * w * h);

    *F = *filter_image(I, w, h, 3, 1);

    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            R[(i * w) + j] = I[(i * w) + j] - F[(i * w) + j];
        }
    }
    return R;
}

int *filter_image(int *I, int w, int h, int d, int tipo) /*contorno*/ {
    /*filtros: 1=minimo, 2=mediana e 3=maximo*/
    if (tipo == 1) {

    }
    if (tipo == 2) {
        
    }
    if (tipo == 3) {
        
    }
}

int *binarize(int *I, int w, int h, int t) {
    int *R, i, j;

    R = malloc (sizeof(int) * w * h);

    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            if (I[(i * w) + j] >= t) R[(i * w) + j] = 255;
            else R[(i * w) + j] = 0;
        }
    }

    return R;
}
