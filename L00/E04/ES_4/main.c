//
//  main.c
//  ES_4
//
//  Created by Andrea Pellegrino on 03/10/2020.
//

#include <stdio.h>
#define N 20

int main(int argc, const char * argv[]) {
    
    FILE* fp;
    char nomefile[N+1];
    int nr, nc;
    int i=0, j=0, k=0, l=0, a=0, b=0;
    int s=0, s_max=0;
    int num;
    int exit=0;
    int min, dim;
    
    
    
    printf("inserisci il nome dle file: ");
    scanf("%s", nomefile);
    
    fp = fopen(nomefile, "r");
    
    fscanf(fp, "%d %d", &nr, &nc);
    
    int m[nr][nc];
    
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            
            fscanf(fp, "%d", &num);
            m[i][j] = num;
        }
    }
    
    printf("\n");
    printf("la matrice e':\n");
    
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    
    min = nc;
    if (nr<nc)
        min = nr;
    
    while(exit==0){
        printf("\ninserisci un numero < %d per continuare, > %d per terminare: ", min, min);
        scanf("%d", &dim);
        if(dim>min)
            exit = 1;
        else{
            
            int mq[dim][dim];
            int m_max[dim][dim];
            
            for(i=0; i<nr+1-dim; i++){  //indice del punto di partenza (righe) della matrice quadrata
                for(j=0; j<nc+1-dim; j++){//indice del punto di partenza (colonna) della matrice quadrata
                    printf("[i] = %d, [j] = %d:\n", i, j);
                    for(k=0; k<dim; k++){
                        for(l=0; l<dim; l++){
                            
                            mq[k][l] = m[i+k][j+l];
                            printf("%d ", mq[k][l]);
                            s = s + mq[k][l];
                        }
                        printf("\n");
                    }
                    printf("\n");
                    if(s > s_max){
                        s_max = s;
                        
                        for(a=0;a<dim;a++){
                            for(b=0;b<dim;b++){
                                m_max[a][b] = mq[a][b];
                            }
                        }
                    }
                    s=0;
                }
            }
            
            printf("\n");
            printf("La sottomatice di dimensione %dx%d massima è:\n", dim, dim);
            for(a=0;a<dim;a++){
                for(b=0;b<dim;b++){
                    printf("%d ", m_max[a][b]);
                }
                printf("\n");
            }
            printf("\n\n");
            
        }
    }
    
    fclose(fp);
    
    return 0;
}
