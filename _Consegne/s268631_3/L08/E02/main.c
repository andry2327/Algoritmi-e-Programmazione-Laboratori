//
//  main.c
//  E01
//
//  Created by Andrea Pellegrino on 23/11/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct valore_pietre{
    
    int n_pietre;
    int val;
}valore_pietre;

typedef struct pietre{
    
    valore_pietre R;  // N rubini
    valore_pietre S;  // N smeraldi
    valore_pietre T;  // N topazi
    valore_pietre Z;  // N zaffiri
    int max_rip;
}stones;

int cond_R(char v);
int cond_S(char v);
int cond_T(char v);
int cond_Z(char v);

int is_next_valid(char P, char next);
int q_pietre(char P, stones pietre);
stones sottr_pietre(char P, stones* pietre);
int is_max_rip(char P, char* sol, int dim_sol, int max_rip);
int is_Z_lower_S(stones *p_in_sol);

void init_str(char *s, int len);

int find_K_sol(int l, int K, int r, stones pietre, int* val_col);

int D_rip(int pos, char* val, stones pietre, stones *p_in_sol, int* curr_valore, int* max_valore, char *sol, char *sol1, int n, int K, int count, int* pf);

int main(int argc, const char * argv[]) {
    
    FILE* fp;
    int N_test;
    int i_test;
    int n_pietre, valore, K, val_col;
    stones pietre;
    
    
    fp = fopen("test_set.txt", "r");  //  very_easy_test_set easy_test_set
    
    if(fp==NULL){
        printf("errore apertura file\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp, "%d", &N_test);
    
    for(i_test=0; i_test<N_test; i_test++){
        
        fscanf(fp, "%d%d%d%d%d%d%d%d%d", &pietre.Z.n_pietre, &pietre.R.n_pietre, &pietre.T.n_pietre, &pietre.S.n_pietre, &pietre.Z.val, &pietre.R.val, &pietre.T.val, &pietre.S.val, &pietre.max_rip);
        
        n_pietre = pietre.Z.n_pietre + pietre.R.n_pietre + pietre.T.n_pietre + pietre.S.n_pietre;
        valore = pietre.Z.n_pietre*pietre.Z.val + pietre.R.n_pietre*pietre.R.val + pietre.T.n_pietre*pietre.T.val + pietre.S.n_pietre*pietre.S.val;
        
        printf("collana con %d zaffiri [valore: %d], %d rubini [valore: %d], %d topazi [valore: %d], %d smeraldi [valore: %d], con %d pietre totali [valore tot: %d], [max rip: %d]:\n\n", pietre.Z.n_pietre, pietre.Z.val, pietre.R.n_pietre, pietre.R.val, pietre.T.n_pietre, pietre.T.val, pietre.S.n_pietre, pietre.S.val, n_pietre, valore, pietre.max_rip);
        
        K = find_K_sol(0, 0.5*(n_pietre+1), n_pietre+1, pietre, &val_col);
        printf("\n");

        printf("lunghezza: %d, valore: %d\n", K, val_col);
        printf("\n\n");
        
    }
    
    fclose(fp);
    
    return 0;
}

int find_K_sol(int l, int K, int r, stones pietre, int* val_col){  // trova la collana di lunghezza massima
    
    int flag = 0;
    char *sol = malloc((K+1)*sizeof(char));
    char *sol1 = malloc((K+1)*sizeof(char));
    stones p_in_sol; p_in_sol.R.n_pietre=0; p_in_sol.S.n_pietre=0; p_in_sol.T.n_pietre=0; p_in_sol.Z.n_pietre=0;
    int curr_valore = 0;
    int max_valore = 0;
    char val[] = {'R', 'S', 'T', 'Z', '\0'};
    int f=1, *pf =&f;
    
    if(l == r-1){  // k massimo = l
        free(sol);
        return l;  // l+1 perchè la lunghezza della collana dipende dalla variabile pos nel calcolo delle D'(n,K), la quale parte da pos=0 -> la lunghezza effettiva è (?)
    }
    
    flag = D_rip(0, val, pietre, &p_in_sol, &curr_valore, &max_valore, sol, sol1, 4, K, 0, pf); init_str(sol, K);
    
    if(max_valore != 0) *val_col = max_valore;
    
    if(flag == 0)  //nessuna collana possbile di lunghezza K
        return find_K_sol(l, 0.5*(l+K), K, pietre, val_col);
    else
        return find_K_sol(K, 0.5*(K+r), r, pietre, val_col);  // esiste almeno una soluzione
}

int D_rip(int pos, char* val, stones pietre, stones *p_in_sol, int* curr_valore, int* max_valore, char *sol, char *sol1, int n, int K, int count, int* pf){
    
    int i;
    
    if (pos >= K){
        if( (*pf==1) && (*curr_valore > *max_valore) && is_Z_lower_S(p_in_sol) ){
            for(i=0; i<K; i++){
                *max_valore = *curr_valore;
                sol1[i] = sol[i];
                printf("%c ", sol[i]);
            }
            //sol1[i] = sol[i];
            *pf=0; //printf("%d", *pf);
            printf("\n");
            return 1;
        }
        return count+1;
    }

    for(i=0; i<4; i++){
        if( (q_pietre(val[i], pietre) > 0) && (pos==0?1:is_next_valid(sol[pos-1], val[i])) && ( (pos >= pietre.max_rip)?(is_max_rip(val[i], sol, pos, pietre.max_rip)):1 ) ){
            
            sol[pos] = val[i];
            
            if (val[i] == 'R'){ pietre.R.n_pietre -= 1; p_in_sol->R.n_pietre += 1;  *curr_valore += pietre.R.val; }
            else if (val[i] == 'S'){ pietre.S.n_pietre -= 1; p_in_sol->S.n_pietre += 1; *curr_valore += pietre.S.val; }
            else if (val[i] == 'T'){ pietre.T.n_pietre -= 1; p_in_sol->T.n_pietre += 1;  *curr_valore += pietre.T.val; }
            else if (val[i] == 'Z'){ pietre.Z.n_pietre -= 1; p_in_sol->Z.n_pietre += 1;  *curr_valore += pietre.Z.val; }
            
            count = D_rip(pos+1, val , pietre, p_in_sol, curr_valore, max_valore, sol, sol1, n, K, count, pf);
            
            if (val[i] == 'R'){ pietre.R.n_pietre += 1; p_in_sol->R.n_pietre -= 1; *curr_valore -= pietre.R.val;}       //backtrack
            else if (val[i] == 'S'){ pietre.S.n_pietre += 1; p_in_sol->S.n_pietre -= 1; *curr_valore -= pietre.S.val;}
            else if (val[i] == 'T'){ pietre.T.n_pietre += 1; p_in_sol->T.n_pietre -= 1; *curr_valore -= pietre.T.val;}
            else if (val[i] == 'Z'){ pietre.Z.n_pietre += 1; p_in_sol->Z.n_pietre -= 1; *curr_valore -= pietre.Z.val;} //
            
        }
    }
    
    sol[pos] = '\0';
    
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
            return pietre.R.n_pietre;
            
        case 'S':
            return pietre.S.n_pietre;
            
        case 'T':
            return pietre.T.n_pietre;
            
        case 'Z':
            return pietre.Z.n_pietre;
            
        default: return -1;
    }
    
}

int is_max_rip(char P, char* sol, int dim_sol, int max_rip){
    
    int i;
    
    for(i=0; i<max_rip; i++){
        if(sol[dim_sol-1-i] != P)
            return 1;
    }
    return 0;
}

int is_Z_lower_S(stones *p_in_sol){
    
    if((p_in_sol->Z.n_pietre) <= (p_in_sol->S.n_pietre))
        return 1;
    return 0;
}

void init_str(char *s, int len){
    
    int i;
    
    for(i=0; i<5; i++)
        s[i] = '\0';
}
