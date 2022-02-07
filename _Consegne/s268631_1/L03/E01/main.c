//
//  main.c
//  ES1
//
//  Created by Andrea Pellegrino on 19/10/2020.
//

#include <stdio.h>
#include <stdlib.h>
#define MAXR 50

void leggiMatrice(int matrice[][MAXR], int dim, int *p_nr, int *p_nc);

int riconosciRegione(int mappa[][MAXR], int n_r, int n_c, int i, int j, int *b, int *h);

int main(int argc, const char * argv[]) {
    
    int nr, nc;
    int r, c;
    int b, h;
    int M[MAXR][MAXR];
    
    leggiMatrice(M, MAXR, &nr, &nc);
    
    for(r=0; r<nr; r++)
        for(c=0; c<nc; c++){
            if(riconosciRegione(M, nr, nc, r, c, &b, &h))
                printf("Rettangolo con estremo in (%d,%d), base %d e altezza %d\n", r, c, b, h);
        }
    printf("\n");
}
       
void leggiMatrice(int matrice[][MAXR], int dim, int *p_nr, int *p_nc){
    
    FILE* fp;
    int i, j;
    
    fp = fopen("mat.txt", "r");
    
    if (fp == NULL){
        printf("errore apertura file mat.txt\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp, "%d%d", p_nr, p_nc);
   
    for(i=0; i<*p_nr; i++)
        for(j=0; j<*p_nc; j++)
            fscanf(fp, "%d", &matrice[i][j]);
    
    printf("Matrice letta:\n");
    printf("\n");
    
    for(i=0; i<*p_nr; i++){
        for(j=0; j<*p_nc; j++){
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    fclose(fp);
}

int riconosciRegione(int mappa[][MAXR], int n_r, int n_c, int i, int j, int *b, int *h){
    
    int rett_found=0; //rett_found = 0 : FALSE, rett_found = 1 : TRUE
    int k=1, l=1;
    
    if(mappa[i][j] == 1){
        rett_found = 1;
        mappa[i][j] = -1;
        while (mappa[i][j+l] == 1){
            mappa[i][j+l] = -1;
            l += 1;
        }
        
        while (mappa[i+k][j] == 1){
            mappa[i+k][j] = -1;
            k += 1;
        }
        *b = l; //base
        *h = k; //altezza
    }

return rett_found;

}
