//
//  main.c
//  E01
//
//  Created by Andrea Pellegrino on 23/11/20.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct pietre{
    
    int R;  // N rubini
    int S;  // N smeraldi
    int T;  // N topazi
    int Z;  // N zaffiri
}stones;

int cond_R(char v);
int cond_S(char v);
int cond_T(char v);
int cond_Z(char v);

int is_next_valid(char P, char next);
int q_pietre(char P, stones pietre);
stones sottr_pietre(char P, stones* pietre);

int sol_K(stones* pietre, int n_pietre, int K);

int find_K_sol(int l, int K, int r, stones pietre);

int D_rip(int pos, char* val, stones pietre, char *sol, int n, int K, int count, int* pf);

int main(int argc, const char * argv[]) {
    
    FILE* fp;
    int N_test;
    int i_test, i;
    int n_pietre, K;
    char *sol1=NULL;
    stones pietre;
    
    
    fp = fopen("easy_test_set.txt", "r");  //  very_easy_test_set easy_test_set
    
    if(fp==NULL){
        printf("errore apertura file\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp, "%d", &N_test);
    
    for(i_test=0; i_test<N_test; i_test++){
        
        fscanf(fp, "%d%d%d%d", &pietre.Z, &pietre.R, &pietre.T, &pietre.S);
        
        n_pietre = pietre.Z + pietre.R + pietre.T + pietre.S;
        
        printf("collana con %d zaffiri, %d rubini, %d topazi, %d smeraldi, con %d pietre totali:\n\n", pietre.Z, pietre.R, pietre.T, pietre.S, n_pietre);
        
        K = find_K_sol(0, 0.5*(n_pietre+1), n_pietre+1, pietre);
        printf("\n");
        
        printf("lunghezza: %d\n", K);
        printf("\n\n");
        
    }
    
    free(sol1);
    fclose(fp);
    
    return 0;
}

int find_K_sol(int l, int K, int r, stones pietre){
    
    int flag = 0;
    char *sol = malloc((K+1)*sizeof(char)); //sol[0] = 'X';
    char val[] = {'R', 'S', 'T', 'Z', '\0'};
    int f=1, *pf =&f;
    
    if(l == r-1){  // k massimo = l
        free(sol);
        return l;  // l+1 perchè la lunghezza della collana dipende dalla variabile pos nel calcolo delle D'(n,K), la quale parte da pos=0 -> la lunghezza effettiva è (?)
    }
    
    flag = D_rip(0, val, pietre, sol, 4, K, 0, pf);
    
    if(flag == 0)  //nessuna collana possbile di lunghezza K
        return find_K_sol(l, 0.5*(l+K), K, pietre);
    else
        return find_K_sol(K, 0.5*(K+r), r, pietre);  // esiste almeno una soluzione
    
}

int D_rip(int pos, char* val, stones pietre, char *sol, int n, int K, int count, int* pf){
    
    int i;
    
    if ((pos >= K) && (*pf==1)){
        for(i=0; i<K; i++){
            printf("%c ", sol[i]);
        }
        
            //sol1[i] = sol[i];
        *pf=0; //printf("%d", *pf);
        printf("\n");
        return count+1;
    }

    for(i=0; i<4; i++){
        if( (q_pietre(val[i], pietre) > 0) && (pos==0?1:is_next_valid(sol[pos-1], val[i])) ){
            
            sol[pos] = val[i];
            
            if (val[i] == 'R') pietre.R = pietre.R - 1;
            else if (val[i] == 'S') pietre.S = pietre.S - 1;
            else if (val[i] == 'T') pietre.T = pietre.T - 1;
            else if (val[i] == 'Z') pietre.Z = pietre.Z - 1;
            
            count = D_rip(pos+1, val , pietre, sol, n, K, count, pf);
            
            if (val[i] == 'R') pietre.R = pietre.R + 1;                   // backtrack
            else if (val[i] == 'S') pietre.S = pietre.S + 1;
            else if (val[i] == 'T') pietre.T = pietre.T + 1;
            else if (val[i] == 'Z') pietre.Z = pietre.Z + 1;              //
        }
    }
    
    return count;
}

int cond_R(char v){
    
    if( (v == 'S') || (v == 'T') )
        return 1;
    return 0;
}

int cond_S(char v){
    
    if( (v == 'S') || (v == 'T') )
        return 1;
    return 0;
}

int cond_T(char v){
    
    if( (v == 'Z') || (v == 'R') )
        return 1;
    return 0;
}

int cond_Z(char v){
    
    if ( (v == 'Z') || (v == 'R') )
        return 1;
    return 0;
}
           
int is_next_valid(char P, char next){
    
    switch(P){
            
        case 'R':
            return cond_R(next);
            
        case 'S':
            return cond_S(next);
            
        case 'T':
            return cond_T(next);
            
        case 'Z':
            return cond_Z(next);
            
        default: return -1;
    
    }
}

int q_pietre(char P, stones pietre){
    
    switch(P){
            
        case 'R':
            return pietre.R;
            
        case 'S':
            return pietre.S;
            
        case 'T':
            return pietre.T;
            
        case 'Z':
            return pietre.Z;
            
        default: return -1;
    }
    
}

