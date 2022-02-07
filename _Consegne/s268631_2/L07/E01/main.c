//
//  main.c
//  E01
//
//  Created by Andrea Pellegrino on 16/11/20.
//

#include <stdio.h>
#include <stdlib.h>

int sol_is_valid(int **grafo, int *sol, int dim_grafo, int dim_sol);

int fact(int n);

int is_in(int a, int *s, int dim_s);

int is_connected(int **grafo, int N, int E);

int C_sempl (int N, int K, int *val, int*sol, int st, int pos, int cnt, int ***g, int E);

int main(int argc, const char * argv[]) {
    
    FILE* fp;
    int N, E; // N: n vertici, E: n archi
    int **grafo;
    int i, K; //K: raggruppamenti
    int c_tot;
    int *val, *sol = NULL;
    
    fp = fopen("g3.txt","r");
    
    if (fp==NULL){
        printf("errore apertura file\n");
        exit(EXIT_SUCCESS);
    }
    
    fscanf(fp, "%d%d", &N, &E);
    
    grafo = malloc(E*sizeof(int*));
    for (i=0; i<E; i++){
        grafo[i] = malloc(2*sizeof(int));
    }
    
    val = malloc(N*sizeof(int));
    
    for(i=0; i<N; i++)  //inizializzazione vettore val
        val[i] = i;
    
    for(i=0; i<E; i++)
        fscanf(fp, "%d %d", &grafo[i][0], &grafo[i][1]);
    
    if(is_connected(grafo, N, E)){
        
        printf ("Vertex Cover di %d elementi e %d archi dati, divisi per dimensione K:\n\n\n", N, E);
        for(K=1; K<N; K++){
            
            sol = malloc(K*sizeof(int));
            printf("K == %d:\n\n", K);
        
            c_tot = C_sempl(N, K, val, sol, 0, 0, 0, &grafo, E);
            printf("\n");
        }
        printf("K = %d:\n\n", K);
        printf("{ ");
        for(i=0;i<K-1;i++){
            printf("%d, ", val[i]);
        }
        printf("%d }\n\n", val[i]);
        
    }else
        printf("Vertex Cover e' l'insieme vuoto\n\n");
    
}

int C_sempl (int N, int K, int *val, int *sol, int st, int pos, int cnt, int ***g, int E){
    
    int i;
    
    if(pos >= K){
        if(sol_is_valid(*g, sol, E, K)){
            
            printf("{ ");
            for(i=0;i<K-1;i++){
                printf("%d, ",sol[i]);
            }
            printf("%d }\n\n", sol[i]);
        }
        
        return cnt+1;
    }
    
    for(i=st; i<N; i++){
        sol[pos] = val[i];
        cnt = C_sempl(N, K ,val, sol, i+1, pos+1, cnt, g, E);
    }
    return cnt;
}

int is_connected(int **grafo, int N, int E){
    
    int i=0,j;
    int a,b;
    int cnt=1;
    int* v = malloc(N*sizeof(int));
    //v = malloc(N*sizeof(int));
    
    for(i=0; i<N; i++)  //inizializzazione vettore
        v[i] = i;
    
    i=0;
    
    while(i<E){   // il meccanismo di controllo fa si che i vertici del grafo corrispondano a all' indice di v[N]
        a = grafo[i][0]; b = grafo[i][1];
        if( v[a] != v[b]){
            for(j=0; j<N; j++)
            if( (v[j] == v[b]) && (j!=a) ){
                    v[j] = v[a];
            }
        }
        i++;
    }
    
    for(j=0; j<N; j++)
        if(v[j] == v[0]){
            cnt++;
            if(cnt >= N)
                return 1;  // la func ritorna 1 (grafo connesso) solo nel momento in cui v[i] è lo stesso per ogni i
        }
    
    return 0;
}

int fact(int n){
    
    if (n==0)
        return 1;
    
    return n*fact(n-1);
}

int sol_is_valid(int **grafo, int *sol, int dim_grafo, int dim_sol){
    
    int i;
    
    for(i=0; i<dim_grafo; i++){
        if( !( is_in(grafo[i][0], sol, dim_sol) || is_in(grafo[i][1], sol, dim_sol) ) ) //entra nell' if() solo se il risultato dell' espressione logica è 1: ( !(0 || 0) ) -> nessuno dei 2 vertici è in sol
            return 0;
    }
    return 1;
}

int is_in(int a, int *s, int dim_s){
    
    int i;
    
    for(i=0; i<dim_s; i++){
        if (a == s[i])
            return 1;
    }
    return 0;
}
