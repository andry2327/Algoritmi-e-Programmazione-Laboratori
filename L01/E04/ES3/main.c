//
//  main.c
//  ES3
//
//  Created by Andrea Pellegrino on 08/10/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NOME 20
#define M_DIM 30
#define MAX_S 100

void ruota(int matrice[][M_DIM], int nr, int nc, char selettore[], int indice, char direzione[], int posizioni);

int main(int argc, const char * argv[]) {
    
    char nome_file[MAX_NOME+1];
    FILE* fp;
    FILE* fp1;
    int i=0, j=0;
    int nr, nc;
    int m[M_DIM][M_DIM];
    int index=0, pos=0;
    char sel[MAX_S+1];
    char dir[MAX_S+1];
    
    printf("inserire il nome dle file: ");
    scanf("%s", nome_file);
    
    fp = fopen(nome_file, "r");
    
    if(fp == NULL){
        printf("errore apertura file %s", nome_file);
        exit(EXIT_FAILURE);
    }
    
    fp1 = fopen("temp.txt", "w+");
    
    if(fp1 == NULL){
        printf("errore apertura file temp");
        exit(EXIT_FAILURE);
    }
    
    
    fscanf(fp, "%d%d", &nr, &nc);
    printf("nr=%d, nc=%d\n", nr, nc);
    
    for(i=0;i<nr;i++){  //lettura matrice da file e scrittura su temp.txt
        for(j=0;j<nc;j++){
            fscanf(fp, "%d", &m[i][j]);
            fprintf(fp1, "%d ", m[i][j]);
        }
        fprintf(fp1, "\n");
    }
    
    for(i=0;i<nr;i++){  //stampo matrice
        for(j=0;j<nc;j++){
        
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    
    

    while(1){
        printf("inserisci la stringa di dati:\n");
        scanf("%s%d%s%d", sel, &index, dir, &pos);
        if(strcmp(sel, "fine") == 0)
            exit(EXIT_SUCCESS);
        ruota(m, nr, nc, sel, index-1, dir, pos);
       
        for(i=0;i<nr;i++){  //stampo matrice
            for(j=0;j<nc;j++){
            
                printf("%d ", m[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
        
    
    
    return 0;
}

void ruota(int matrice[][M_DIM], int nr, int nc, char selettore[], int indice, char direzione[], int posizioni){
    
    int i=0, j=0, k=0;
    int r=0, c=0;
    int t=0;
    int top=0;
    int base[4][2] = {{0, 1},  //sx
                      {0,-1},  //dx
                      {1, 0},  //su
                      {-1,0} };  //giu
    
    if(strcmp(direzione,"destra")==0){
        t = matrice[indice][nc-1];
        r = base[1][0];
        c = base[1][1];
        top = nc;
    }
    if(strcmp(direzione,"giu")==0){
        t = matrice[nr-1][indice];
        r = base[3][0];
        c = base[3][1];
        top = nr;
    }
    if(strcmp(direzione,"sinistra")==0){
        t = matrice[indice][0];
        r = base[0][0];
        c = base[0][1];
        top = nc;
    }
    if(strcmp(direzione,"su")==0){
        t = matrice[0][indice];
        r = base[2][0];
        c = base[2][1];
        top = nr;
    }
    while(i<posizioni){
        for(j=0; j<top; j++){
            if(strcmp(direzione,"destra")==0){
                k = (nc - 1) - j;
                matrice[indice][k] =  matrice[indice+r][k+c];
            }
            if(strcmp(direzione,"giu")==0){
                k = (nr - 1) - j;
                matrice[k][indice] =  matrice[k+r][indice+c];
            }
            if(strcmp(direzione,"sinistra")==0){
                k = j;
                matrice[indice][k] =  matrice[indice+r][k+c];
            }
            if(strcmp(direzione,"su")==0){
                k = j;
                matrice[k][indice] =  matrice[k+r][indice+c];
            }
      
        }
        if(strcmp(direzione,"destra")==0){
            matrice[indice][0] = t;
        }
        if(strcmp(direzione,"giu")==0){
            matrice[0][indice] = t;
        }
        if(strcmp(direzione,"sinistra")==0){
            matrice[indice][nc-1] = t;
        }
        if(strcmp(direzione,"su")==0){
            matrice[nr-1][indice] = t;
        }
        i++;
    }
 
    
}
