//
//  main.c
//  E02
//
//  Created by Andrea Pellegrino on 10/11/2020.
//

#include <stdio.h>
#include <stdlib.h>

int **malloc2d(int nr, int nc);

void separa(int** mat, int nr, int nc, int *white, int *black);

int main(int argc, const char * argv[]) {
    
    FILE* fp;
    int **p_m;  //p_m[][]
    int nr, nc;
    int i, j;
    int* bianco = NULL, *nero = NULL;
    
    fp = fopen("m.txt", "r");
    
    if (fp==NULL){
        printf("errore apertura file");
        exit(EXIT_SUCCESS);
    }
    
    fscanf(fp, "%d%d", &nr, &nc);
    
    p_m = malloc2d(nr, nc);
    
    for(i=0; i<nr; i++)  //lettura matrice
        for(j=0; j<nc; j++)
            fscanf(fp, "%d", &p_m[i][j]);
    
    separa(p_m, nr, nc, bianco, nero);
    
    fclose(fp);
    
    return 0;
}

int **malloc2d(int nr, int nc){
    
    int **m;
    int i;
    
    m = malloc(nr*sizeof(int*));
    for(i=0; i<nr; i++)
        m[i] = malloc(nc*sizeof(int));
    
    return m;
}

void separa(int** mat, int nr, int nc, int *white, int *black){
    
    int i, j = 0;
    black = malloc( ((nr*nc)-(int)(0.5*nr*nc)) * (sizeof(int)) );
    white = malloc( (int)(0.5*nr*nc) * (sizeof(int)) );
    
    for(i=0; i<nr; i++)
        for(j=0; j<nc; j++){
        
            if ( (i*nc+j)%2 == 0 )
                black[(i*nc+j)/2] = mat[i][j];
            else
                white[(i*nc+j-1)/2] = mat[i][j];
        }

    printf("black: [ ");
    for(j=0; j<((nr*nc)-(int)(0.5*nr*nc)); j++)
        printf("%d ", black[j]);
    printf("]\n");
    
    printf("white: [ ");
    for(j=0; j<((int)(0.5*nr*nc)); j++)
        printf("%d ", white[j]);
    printf("]\n");
    
    free(black);
    free(white);
    
    printf("\n");
    
}
