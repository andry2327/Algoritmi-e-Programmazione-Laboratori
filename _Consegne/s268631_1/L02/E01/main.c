//
//  main.c
//  ES1
//
//  Created by Andrea Pellegrino on 12/10/2020.
//

#include <stdio.h>
#include <stdlib.h>
#define DIM 50

int main(int argc, const char * argv[]) {
    
    FILE* fp;
    int nr, nc;
    int i, j;
    int k=1, l=1;
    int rett_max[3][5] = {{0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0}};         //len; h; area  (i,j; len; h; area)
    int mappa[DIM][DIM];
    
    fp = fopen("mappa.txt", "r");
    
    if (fp == NULL){
        printf("errore apertura file mappa.txt\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp, "%d%d", &nr, &nc);
    
    for(i=0; i<nr; i++)
        for(j=0; j<nc; j++)
            fscanf(fp, "%d", &mappa[i][j]);
    
    fclose(fp);
            
    for(i=0; i<nr; i++)
        for(j=0; j<nc; j++){
        
            if(mappa[i][j] == 1){
                mappa[i][j] = -1;
                while (mappa[i][j+l] == 1){ //controlllo lunghezza
                    mappa[i][j+l] = -1;
                    l += 1;
                }
                
                while (mappa[i+k][j] == 1){  //controlllo altezza
                    mappa[i+k][j] = -1;
                    k += 1;
                }
                
                if (l > rett_max[0][2]){
                    rett_max[0][0] = i;  //rett_max_i
                    rett_max[0][1] = j;  //rett_max_j
                    rett_max[0][2] = l; //rett_max_len
                    rett_max[0][3] = k;  //rett_max_h
                    rett_max[0][4] = l * k;  //rett_max_area
                }
                
                if (k > rett_max[1][3]){
                    rett_max[1][0] = i;
                    rett_max[1][1] = j;
                    rett_max[1][2] = l;
                    rett_max[1][3] = k;
                    rett_max[1][4] = l * k;
                }
                
                if (l*k > rett_max[2][4]){
                    rett_max[2][0] = i;
                    rett_max[2][1] = j;
                    rett_max[2][2] = l;
                    rett_max[2][3] = k;
                    rett_max[2][4] = l * k;
                    
                }
                
                l=1; k=1;
            }
    }
    
    printf("Max Base: estr. sup. SX = <%d><%d>, b = %d, h = %d, area = %d\n", rett_max[0][0], rett_max[0][1], rett_max[0][2], rett_max[0][3], rett_max[0][4]);
    printf("Max Altezza: estr. sup. SX = <%d><%d>, b = %d, h = %d, area = %d\n", rett_max[1][0], rett_max[1][1], rett_max[1][2], rett_max[1][3], rett_max[1][4]);
    printf("Max Area: estr. sup. SX = <%d><%d>, b = %d, h = %d, area = %d\n", rett_max[2][0], rett_max[2][1], rett_max[2][2], rett_max[2][3], rett_max[2][4]);
    printf("\n");

}
