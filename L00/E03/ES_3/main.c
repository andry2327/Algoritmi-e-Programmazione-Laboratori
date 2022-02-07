//
//  main.c
//  ES_3
//
//  Created by Andrea Pellegrino on 02/10/2020.
//

#include <stdio.h>
#define maxN 30

void ruota(int v[maxN], int N, int P, int dir);

int main(int argc, const char * argv[]) {
    
    int N;
    int i;
    int P;
    int dir;
    int exit=0;
    
    do{
        printf("inserisci la dimensione del vettore: ");
        scanf("%d", &N);
        
        if (N > maxN)
            printf("la dimensione del vettoredeve essere minore di 30\n");
        
    }while(N > maxN);
    
    int v[N];
    
    printf("inserisci il vettore:\n");
    
    for(i=0;i<N;i++){
        printf("[%d]: ", i);
        scanf("%d", &v[i]);
    }
    
    printf("\nil vettore e': ");
    for(i=0;i<N;i++){
        printf("%d ", v[i]);
    }
    printf("\n\n");
    
    while(exit == 0){
        printf("inserisci rotazione e direzione: ");
        scanf("%d %d", &P, &dir);
        if(P == 0){
            exit = 1;
        }
        else{
            if((dir != (-1)) && (dir != 1))
                printf("errore rotazione");
            else{
                printf("\nP: %d e dir: %d\n", P, dir);
                ruota(v, N, P, dir);
            }
        }
    }
    
    return 0;
}

void ruota(int v[maxN], int N, int P, int dir){
    
    int i = 0;
    int j = 0;
    int k = 0;
    int t = 0;
    

    while(i<P){
        
        if(dir == -1){
            t = v[N-1];
        }else{
            t = v[0];
        }
        
        for(j=0; j<N; j++){
            if(dir == -1){
                k = (N - 1) - j ;
            }else{
                k = j;
            }
            
            v[k] = v[k+dir];
        }
        
        v[k] = t;
        i = i + 1;  //serve per il numero di singole rotazioni
    }
    
    printf("il vettore ruotato e': ");
    for(i=0;i<N;i++){
        printf("%d ", v[i]);
    }
    printf("\n\n");
}
