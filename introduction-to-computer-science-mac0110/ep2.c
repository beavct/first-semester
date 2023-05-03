#include <stdio.h>
#define PI 3.14159
#define RAIO_AP 200
#define RAIO_ZA 2000 /*zona de alerta*/
#define DELTA_ALARME 60
#define EPS_COS 0.000001 /*precisão para o cálculo de cosseno*/
#define EPS 0.01 /*precisão para os valores contendo metro*/

double dist_percorrida (double xv1, double yv1, double xv2, double yv2);
double dist_origem (double x, double y);
double velocidade (double x0, double y0, double x1, double y1, double deltaT);
int iguais (double x, double y);
double cosseno (double theta, double epsilon);
double fatorial (double d);
double potencia (double e, int pot);
double distancia (double H, double cos);
double raiz (double x, double epsilon);
int localiza (double xi, double yi, double div, double xj, double yj, double djv, double xk, double yk, double dkv, double *xv, double *yv);
int intercepta (double x0, double y0, double x1, double y1, double *x, double *y);

int main (){
    int casos, IDv;
    /* Dados para o cálcula da posição prévia*/
    double Xi1, Yi1, Hi1, thetaI1; 
    double Xj1, Yj1, Hj1, thetaJ1;
    double Xk1, Yk1, Hk1, thetaK1; 
    /* Dados para o cálcula da posição atual*/ 
    double deltaT;  
    double Xi2, Yi2, Hi2, thetaI2; 
    double Xj2, Yj2, Hj2, thetaJ2;
    double Xk2, Yk2, Hk2, thetaK2;
    /*IDs de cada antena*/
    int IDi1, IDi2, IDj1, IDj2, IDk1, IDk2;
    /*Localização e distância em relação as antenas prévias*/
    double xLP, yLP, diP, djP, dkP; 
    /*Localização e distância em relação as antenas atuais*/
    double xLA, yLA, diA, djA, dkA; 
    /*Outras infos*/
    double dist_per, dista_origem, vel_med;
    /*Usado para saber quando parar a análise de um veículo*/ 
    int continuar = 1;
    /*Variáveis usadas caso a trajetória intercepte a AP*/
    double xAP, yAP, deltaTAP, distAP;

    FILE *arq;
    char filename [256];

    printf ("Programa-demo para o Sistema de Monitoramento\n\n\n"
    "Digite o nome do arquivo com os dados a serem processados:\n");
    scanf ("%s", filename);

    arq = fopen(filename, "r");

    if (arq == NULL) {
        printf ("Nao consegui abrir o arquivo %s.\n", filename);
        return 0;
    }

    fscanf (arq, "%d", &casos);
    printf ("Casos a serem analisados: %d\n", casos);

    while (casos > 0 && continuar) {
        fscanf (arq, "%d", &IDv);
        fscanf (arq, "%d %lf %lf %lf %lf", &IDi1, &Xi1, &Yi1, &Hi1, &thetaI1); /*Lê as variáveis da antena I na posição prévia*/
        fscanf (arq, "%d %lf %lf %lf %lf", &IDj1, &Xj1, &Yj1, &Hj1, &thetaJ1); /*Lê as variáveis da antena J na posição prévia*/
        fscanf (arq, "%d %lf %lf %lf %lf", &IDk1, &Xk1, &Yk1, &Hk1, &thetaK1); /*Lê as variáveis da antena K na posição prévia*/
        fscanf (arq, "%lf", &deltaT); /*Lê o intervalo de tempo*/
        fscanf (arq, "%d %lf %lf %lf %lf", &IDi2, &Xi2, &Yi2, &Hi2, &thetaI2); /*Lê as variáveis da antena I na posição atual*/
        fscanf (arq, "%d %lf %lf %lf %lf", &IDj2, &Xj2, &Yj2, &Hj2, &thetaJ2); /*Lê as variáveis da antena J na posição atual*/
        fscanf (arq, "%d %lf %lf %lf %lf", &IDk2, &Xk2, &Yk2, &Hk2, &thetaK2); /*Lê as variáveis da antena K na posição atual*/

        diP = distancia (Hi1, thetaI1); djP = distancia (Hj1, thetaJ1); dkP = distancia (Hk1, thetaK1);
        diA = distancia (Hi2, thetaI2); djA = distancia (Hj2, thetaJ2); dkA = distancia (Hk2, thetaK2);

        printf ("IDENTIFICACAO: veiculo %d\n\n", IDv);
        printf ("Antenas na posicao previa:\n");
        printf ("id | posicao | H (m) | theta (graus) | distancia (m)\n");
        printf ("%d | (%.2f, %.2f) | %.2f | %.2f | %.2f\n", IDi1, Xi1, Yi1, Hi1, thetaI1, diP);
        printf ("%d | (%.2f, %.2f) | %.2f | %.2f | %.2f\n", IDj1, Xj1, Yj1, Hj1, thetaJ1, djP);
        printf ("%d | (%.2f, %.2f) | %.2f | %.2f | %.2f\n\n", IDk1, Xk1, Yk1, Hk1, thetaK1, dkP);

        if (localiza (Xi1, Yi1, diP, Xj1, Yj1, djP, Xk1, Yk1, dkP, &xLP, &yLP) == 0) {
            printf ("Nao foi possivel calcular a localizacao inicial do veiculo %d\n\n", IDv);
            printf ("Nao foi possivel determinar a situacao do veiculo: %d\n\n\n\n\n", IDv);
            continuar = 0;
        }
        else {
            localiza (Xi1, Yi1, diP, Xj1, Yj1, djP, Xk1, Yk1, dkP, &xLP, &yLP);
            printf ("Localizacao previa: (%.2f,%.2f)\n\n", xLP, yLP);            
        }

        printf ("Intervalo de tempo: %.2f segundos\n\n", deltaT);
        printf ("Antenas a posicao atual\n");
        printf ("id | posicao | H (m) | theta (graus) | distancia (m)\n");
        printf ("%d | (%.2f, %.2f) | %.2f | %.2f | %.2f\n", IDi2, Xi2, Yi2, Hi2, thetaI2, diA);
        printf ("%d | (%.2f, %.2f) | %.2f | %.2f | %.2f\n", IDj2, Xj2, Yj2, Hj2, thetaJ2, djA);
        printf ("%d | (%.2f, %.2f) | %.2f | %.2f | %.2f\n\n", IDk2, Xk2, Yk2, Hk2, thetaK2, dkA);

        if (localiza (Xi2, Yi2, diA, Xj2, Yj2, djA, Xk2, Yk2, dkA, &xLA, &yLA) == 0) {
            printf ("Nao foi possivel calcular a localizacao atual do veiculo %d\n\n", IDv);
            printf ("Nao foi possivel determinar a situacao do veiculo: %d\n\n\n\n\n", IDv);
            continuar = 0;
        }
        else {
            localiza (Xi2, Yi2, diA, Xj2, Yj2, djA, Xk2, Yk2, dkA, &xLA, &yLA);
            printf ("Localizacao atual: (%.2f,%.2f)\n\n", xLA, yLA);            
        }

        dist_per = dist_percorrida (xLP, yLP, xLA, yLA); vel_med = velocidade (xLP, yLP, xLA, yLA, deltaT); dista_origem = dist_origem (xLA, yLA);

        printf ("Distancia percorrida: %.2f\n", dist_per);
        printf ("Velocidade: %.2f m/s\n\n", vel_med);
        printf ("Distancia da origem: %.2f\n", dista_origem);

        if (potencia (dista_origem, 2) < potencia (RAIO_AP, 2)) {

            if (vel_med == 0) printf ("O veiculo esta estacionado na AP\n\n");
            else printf ("O veiculo esta em movimento na AP\n\n");
            printf ("*************************************\n");
            printf ("  ALARME, ALARME, ALARME, ALARME !!\n");
            printf ("       Veiculo esta na AP !\n");
            printf ("*************************************\n\n\n\n\n");             
        }
        else if (potencia (dista_origem, 2) < potencia (RAIO_ZA, 2) && potencia (dista_origem, 2) > potencia (RAIO_AP, 2)) {
            if (vel_med == 0) printf ("O veiculo esta estacionado na ZONA DE ALERTA\n\n");
            else printf ("O veiculo esta em movimento na ZONA DE ALERTA\n\n");

            if (!intercepta (xLP, yLP, xLA, yLA, &xAP, &yAP))
                printf ("Trajetoria NAO INTERCEPTARA AP\n\n\n\n\n");
            
            else {
                printf ("Trajetoria INTERCEPTARA AP\n");
                intercepta (xLP, yLP, xLA, yLA, &xAP, &yAP);
                distAP = raiz (potencia ((xAP-xLA), 2) + potencia ((yAP - yLA), 2), EPS);
                printf ("Distancia atual a AP e de %.2f metros\n", distAP);
                deltaTAP = distAP / vel_med;
                printf ("Interseccao ocorrera em %.2f segundos,\n", deltaTAP);
                printf ("na coordenada (%.2f,%.2f)\n", xAP, yAP);
                
                if (deltaTAP <= DELTA_ALARME) {
                    printf ("*************************************\n");
                    printf ("  ALARME, ALARME, ALARME, ALARME !!\n");
                    printf ("      Invasao iminente !\n");
                    printf ("*************************************\n\n\n\n\n");
                }
                else printf ("\n\n\n\n\n");
            }
        }

        else if (potencia (dista_origem, 2) > potencia (RAIO_ZA, 2)) {
            if (vel_med == 0) printf ("Veiculo estacionado FORA da zona de alerta\n\n\n\n\n");
            else printf ("Veiculo em movimento FORA da zona de alerta\n\n\n\n\n");
        }
    casos--;
    }
    fclose (arq);
    return 0;
}

int intercepta (double x0, double y0, double x1, double y1, double *x, double *y) {
    double t1, t2;
    double a, b, c, delta;

    a = (potencia ((x1 - x0), 2) + potencia ((y1 - y0), 2));
    b = ((2 * x1 *(x1 - x0)) + (2 * y1 * (y1 - y0)));
    c = - (RAIO_AP * RAIO_AP) + (x1 * x1) + (y1 * y1);
    delta = ((b * b) - (4 * a * c));

    if (delta <= 0) return 0; /*a trajetória não intercepta a AP*/
    else {
        t1 = (-b + raiz (delta, EPS)) / (2 * a);
        t2 = (-b - raiz (delta, EPS)) / (2 * a);
    }

    if (t1 < 0 && t2 < 0) return 0;    
    else if (t1 < t2){
        if (t1 > 0){
            *x = x1 + (t1 * (x1 - x0));
            *y = y1 + (t1 * (y1 - y0));
            return 1; 
        }
        else {
            *x = x1 + (t2 * (x1 - x0));
            *y = y1 + (t2 * (y1 - y0));
            return 1;
        }
    }
    else { /*t2 < t1*/
        if (t2 > 0){
            *x = x1 + (t2 * (x1 - x0));
            *y = y1 + (t2 * (y1 - y0));
            return 1;
        }
        else {
            *x = x1 + (t1 * (x1 - x0));
            *y = y1 + (t1 * (y1 - y0));
            return 1;
        }
    }

}

double velocidade (double x0, double y0, double x1, double y1, double deltaT) {
    double velocidade, deltaS2, deltaS;

    deltaS2 = potencia ((x1 - x0), 2) + potencia ((y1 - y0), 2);
    deltaS = raiz (deltaS2, EPS);

    velocidade = deltaS / deltaT;

    if (velocidade < 0) velocidade = -velocidade;

    return velocidade;
}

double distancia (double H, double theta){
    double dist;
    dist = H * cosseno (theta, EPS);
    return dist;
}

double potencia (double e, int pot) {
    int cont = 0; double pote = 1;
    while (cont != pot) { pote = pote * e; cont ++;}
    return pote;
}

double cosseno (double theta, double epsilon) {
    double cosx = 0, fat = 0, sinal = 1, rad, n = 1, d = 1, termo = 0, parar = 0, compara;

    rad = (PI * theta) / 180;

    while (parar != 1) {
        termo = (n / d) * sinal;
        n = potencia (rad, 2); fat = fat + 2; d = fatorial (fat), rad = n;

        if (termo < 0 ) compara = -termo;
        else compara = termo;
        if (compara < epsilon) parar = 1;
        else {
            cosx = cosx + termo; sinal = -sinal;
        }
    }
    cosx = cosx + termo;
    return cosx;
}

double fatorial (double d) {
    double fat = 1;
    do { fat = fat * d; d--;} while (d > 1);
    return fat;
}

int iguais (double x, double y) {
    if (x - y < EPS && y - x < EPS ) return 1;
    else return 0;
}

int localiza (double xi, double yi, double div, double xj, double yj, double djv, double xk, double yk, double dkv, double *xv, double *yv) {
    double P1, P2, Q1, Q2; 

    if (iguais(xi, xj) == 0 && iguais(xi, xk) == 0) { /*usa ij e ik*/
        P1 = ((xi *xi) - (xj * xj) + (yi * yi) - (yj * yj) - (div *div) + (djv * djv)) / (2 * (xi - xj)); 
        Q1 = (yj - yi) / (xi - xj);

        P2 = ((xi *xi) - (xk * xk) + (yi * yi) - (yk * yk) - (div *div) + (dkv * dkv)) / (2 * (xi - xk)); 
        Q2 = (yk - yi) / (xi - xk);

        *yv = (P2 - P1) / (Q1 - Q2);
        *xv = P1 + (Q1 * *yv);
    }
    else if (iguais(xj, xi) == 0 && iguais(xj, xk)) { /*usa ji e jk*/
        P1 = ((xj *xj) - (xi * xi) + (yj * yj) - (yi * yi) - (djv *djv) + (div * div)) / (2 * (xj - xi)); 
        Q1 = (yi - yj) / (xj - xi);

        P2 = ((xj *xj) - (xk * xk) + (yj * yj) - (yk * yk) - (djv *djv) + (dkv * dkv)) / (2 * (xj - xk)); 
        Q2 = (yk - yj) / (xj - xk);

        *yv = (P2 - P1) / (Q1 - Q2);
        *xv = P1 + (Q1 * *yv);
    }
    else if (iguais(xk, xi) == 0 && iguais(xk, xj) == 0) { /*usa ki, kj*/
        P1 = ((xk *xk) - (xi * xi) + (yk * yk) - (yi * yi) - (dkv *dkv) + (div * div)) / (2 * (xk - xi)); 
        Q1 = (yi - yk) / (xk - xi);

        P2 = ((xk *xk) - (xj * xj) + (yk * yk) - (yj * yj) - (dkv *dkv) + (djv * djv)) / (2 * (xk - xj)); 
        Q2 = (yj - yk) / (xk - xj);

        *yv = (P2 - P1) / (Q1 - Q2);
        *xv = P1 + (Q1 * *yv);
    }
    else if (iguais (xi, xj) && iguais (xi, xk)) { /*impossível calcular a posição*/
        return 0;
    }
    else { 
        P1 = ((xi *xi) - (xj * xj) + (yi * yi) - (yj * yj) - (div *div) + (djv * djv)) / (2 * (xi - xj)); 
        Q1 = (yj - yi) / (xi - xj);

        P2 = ((xi *xi) - (xk * xk) + (yi * yi) - (yk * yk) - (div *div) + (dkv * dkv)) / (2 * (xi - xk)); 
        Q2 = (yk - yi) / (xi - xk);

        *yv = (P2 - P1) / (Q1 - Q2);
        *xv = P1 + (Q1 * *yv);
    }
    return 1;
}

double raiz (double x, double epsilon) {
    double rant = x, ratu = 0;

    if (x < epsilon) return 0;
    else {
        ratu = (rant/2) + (x/(2*rant));        
        while (rant - ratu >= epsilon) {
            rant = ratu;
            ratu = (rant/2) + (x/(2*rant));
        }
    }      
    return rant;  
}

double dist_origem (double x, double y) {
    double dist;
    dist = raiz (((x*x) + (y*y)), EPS);
    if (x == 0 && y == 0) dist = 0;
    return dist;
}

double dist_percorrida (double xv1, double yv1, double xv2, double yv2) {
    double dist;
    dist = raiz ((((xv2 - xv1) * (xv2 - xv1)) + ((yv2 - yv1) * (yv2 - yv1))), EPS);
    if ((xv2 - xv1) == 0 && (yv2 - yv1) == 0) dist = 0;
    return dist;
}
