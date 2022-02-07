//
//  main.c
//  E02
//
//  Created by Andrea Pellegrino on 08/12/20.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct pietre{
    
    int R;  // N rubini
    int S;  // N smeraldi
    int T;  // N topazi
    int Z;  // N zaffiri
}stones;

int max(int a, int b);
int**** malloc_struttura(stones pietre, int****known_l);

int cond_Z(char v);
int cond_R(char v);
int cond_T(char v);
int cond_S(char v);

int fZ(int**** known_l_Z, int**** known_l_R, int**** known_l_T, int**** known_l_S, int l, stones pietre);
int fR(int**** known_l_Z, int**** known_l_R, int**** known_l_T, int**** known_l_S, int l, stones pietre);
int fT(int**** known_l_Z, int**** known_l_R, int**** known_l_T, int**** known_l_S, int l, stones pietre);
int fS(int**** known_l_Z, int**** known_l_R, int**** known_l_T, int**** known_l_S, int l, stones pietre);

int find_l(int**** known_l_Z, int**** known_l_R, int**** known_l_T, int**** known_l_S, stones pietre);

void free_struttura(int**** known_l, stones pietre);

int main(int argc, const char * argv[]) {
    
    FILE* fp;
    stones pietre; pietre.Z=0; pietre.R=0; pietre.T=0; pietre.S=0;
    int N_test;
    int i_test;
    int n_pietre;
    int**** known_l_Z=NULL; // int known_l [Z][R][T][S]
    int**** known_l_R=NULL; // int known_l [Z][R][T][S]
    int**** known_l_T=NULL; // int known_l [Z][R][T][S]
    int**** known_l_S=NULL; // int known_l [Z][R][T][S]
    
    fp = fopen("easy_test_set.txt", "r");  //  very_very_easy_test_set       very_easy_test_set       easy_test_set    hard_test_set
    
    if(fp==NULL){
        printf("errore apertura file\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp, "%d", &N_test);
    
    for(i_test=0; i_test<N_test; i_test++){
        
        fscanf(fp, "%d%d%d%d", &pietre.Z, &pietre.R, &pietre.T, &pietre.S);
        
        known_l_Z = malloc_struttura(pietre, known_l_Z);
        known_l_R = malloc_struttura(pietre, known_l_R);
        known_l_T = malloc_struttura(pietre, known_l_T);
        known_l_S = malloc_struttura(pietre, known_l_S);
        
        n_pietre = pietre.Z + pietre.R + pietre.T + pietre.S ;
        
        printf("collana con %d zaffiri, %d rubini, %d topazi, %d smeraldi, con %d pietre totali:\n\n", pietre.Z, pietre.R, pietre.T, pietre.S, n_pietre);

        printf("lunghezza: %d\n", find_l(known_l_Z, known_l_R, known_l_T, known_l_S, pietre));
        printf("\n\n");
        
    }

    free_struttura(known_l_Z, pietre);
    free_struttura(known_l_R, pietre);
    free_struttura(known_l_T, pietre);
    free_struttura(known_l_S, pietre);
    
    return 0;
}

int find_l(int**** known_l_Z, int**** known_l_R, int**** known_l_T, int**** known_l_S, stones pietre){
    
    int l=0, max_l=0;
    
    if(pietre.Z > 0){
        pietre.Z -= 1;
        l = fZ(known_l_Z, known_l_R, known_l_T, known_l_S, l+1, pietre);
        if(known_l_Z[pietre.Z][pietre.R][pietre.T][pietre.S] < l) known_l_Z[pietre.Z][pietre.R][pietre.T][pietre.S] = l;
        pietre.Z += 1;
        if(l>max_l) max_l=l; l=0;
    }
    
    if(pietre.R > 0){
        pietre.R -= 1;
        l = fR(known_l_Z, known_l_R, known_l_T, known_l_S, l+1, pietre);
        if(known_l_R[pietre.Z][pietre.R][pietre.T][pietre.S] < l) known_l_R[pietre.Z][pietre.R][pietre.T][pietre.S] = l;
        pietre.R += 1;
        if(l>max_l) max_l=l; l=0;
    }
    
    if(pietre.T > 0){
        pietre.T -= 1;
        l = fT(known_l_Z, known_l_R, known_l_T, known_l_S, l+1, pietre);
        if(known_l_T[pietre.Z][pietre.R][pietre.T][pietre.S] < l) known_l_T[pietre.Z][pietre.R][pietre.T][pietre.S] = l;
        pietre.T += 1;
        if(l>max_l) max_l=l; l=0;
    }
    
    if(pietre.S > 0){
        pietre.S -= 1;
        l = fS(known_l_Z, known_l_R, known_l_T, known_l_S, l+1, pietre);
        if(known_l_S[pietre.Z][pietre.R][pietre.T][pietre.S] < l) known_l_S[pietre.Z][pietre.R][pietre.T][pietre.S] = l;
        pietre.S += 1;
        if(l>max_l) max_l=l; l=0;
    }
    
    return max_l;
}

int fZ(int**** known_l_Z, int**** known_l_R, int**** known_l_T, int**** known_l_S, int l, stones pietre){

    int l1=-1, l2=-1, f=1; //printf("%d\n", known_l[pietre.Z][pietre.R][pietre.T][pietre.S]);
    
    if( known_l_Z[pietre.Z][pietre.R][pietre.T][pietre.S] != -1 ) return known_l_Z[pietre.Z][pietre.R][pietre.T][pietre.S]; // caso terminale 1
    
    if (pietre.Z > 0){
        f=0;
        pietre.Z -= 1;
        l1 = fZ(known_l_Z, known_l_R, known_l_T, known_l_S, l+1, pietre);
        if(known_l_Z[pietre.Z][pietre.R][pietre.T][pietre.S] < l1) known_l_Z[pietre.Z][pietre.R][pietre.T][pietre.S] = l1;
        pietre.Z += 1; // backtrack
    }
    
    if (pietre.R > 0){
        f=0;
        pietre.R -= 1;
        l2 = fR(known_l_Z, known_l_R, known_l_T, known_l_S, l+1, pietre);
        if(known_l_R[pietre.Z][pietre.R][pietre.T][pietre.S] < l2) known_l_R[pietre.Z][pietre.R][pietre.T][pietre.S] = l2;
        pietre.R += 1; // backtrack
    }
    
    if(f){ // caso terminale 2
        known_l_Z[pietre.Z][pietre.R][pietre.T][pietre.S] = l;
        return l;
    }else{
        known_l_Z[pietre.Z][pietre.R][pietre.T][pietre.S] = max(l1, l2);
        return known_l_Z[pietre.Z][pietre.R][pietre.T][pietre.S];
    }
}

int fR(int**** known_l_Z, int**** known_l_R, int**** known_l_T, int**** known_l_S, int l, stones pietre){
    
    int l1=-1, l2=-1, f=1;
    
    if( known_l_R[pietre.Z][pietre.R][pietre.T][pietre.S] != -1 ) return known_l_R[pietre.Z][pietre.R][pietre.T][pietre.S]; // caso terminale 1
    
    
    if (pietre.S > 0){
        f=0;
        pietre.S -= 1;
        l1 = fS(known_l_Z, known_l_R, known_l_T, known_l_S, l+1, pietre);
        if(known_l_S[pietre.Z][pietre.R][pietre.T][pietre.S] < l1) known_l_S[pietre.Z][pietre.R][pietre.T][pietre.S] = l1;
        pietre.S += 1; // backtrack
    }
    
    if (pietre.T > 0){
        f=0;
        pietre.T -= 1;
        l2 = fT(known_l_Z, known_l_R, known_l_T, known_l_S, l+1, pietre);
        if(known_l_T[pietre.Z][pietre.R][pietre.T][pietre.S] < l2) known_l_T[pietre.Z][pietre.R][pietre.T][pietre.S] = l2;
        pietre.T += 1; // backtrack
    }
    
    if(f){ // caso terminale 2
        known_l_R[pietre.Z][pietre.R][pietre.T][pietre.S] = l;
        return l;
    }else{
        known_l_R[pietre.Z][pietre.R][pietre.T][pietre.S] = max(l1, l2);
        return known_l_R[pietre.Z][pietre.R][pietre.T][pietre.S];
    }
}

int fT(int**** known_l_Z, int**** known_l_R, int**** known_l_T, int**** known_l_S, int l, stones pietre){
   
    int l1=-1, l2=-1, f=1;
    
    if( known_l_T[pietre.Z][pietre.R][pietre.T][pietre.S] != -1 ) return known_l_T[pietre.Z][pietre.R][pietre.T][pietre.S]; // caso terminale 1
    
    if (pietre.Z > 0){
        f=0;
        pietre.Z -= 1;
        l1 = fZ(known_l_Z, known_l_R, known_l_T, known_l_S, l+1, pietre);
        if(known_l_Z[pietre.Z][pietre.R][pietre.T][pietre.S] < l1) known_l_Z[pietre.Z][pietre.R][pietre.T][pietre.S] = l1;
        pietre.Z += 1; // backtrack
    }
    
    if (pietre.R > 0){
        f=0;
        pietre.R -= 1;
        l2 = fR(known_l_Z, known_l_R, known_l_T, known_l_S, l+1, pietre);
        if(known_l_R[pietre.Z][pietre.R][pietre.T][pietre.S] < l2) known_l_R[pietre.Z][pietre.R][pietre.T][pietre.S] = l2;
        pietre.R += 1; // backtrack
    }
    
    if(f){ // caso terminale 2
        known_l_T[pietre.Z][pietre.R][pietre.T][pietre.S] = l;
        return l;
    }else{
        known_l_T[pietre.Z][pietre.R][pietre.T][pietre.S] = max(l1, l2);
        return known_l_T[pietre.Z][pietre.R][pietre.T][pietre.S];
    }
}

int fS(int**** known_l_Z, int**** known_l_R, int**** known_l_T, int**** known_l_S, int l, stones pietre){
    
    int l1=-1, l2=-1, f=1;
    
    if( known_l_S[pietre.Z][pietre.R][pietre.T][pietre.S] != -1 ) return known_l_S[pietre.Z][pietre.R][pietre.T][pietre.S]; // caso terminale 1
    
    if (pietre.S > 0){
        f=0;
        pietre.S -= 1;
        l1 = fS(known_l_Z, known_l_R, known_l_T, known_l_S, l+1, pietre);
        if(known_l_S[pietre.Z][pietre.R][pietre.T][pietre.S] < l1) known_l_S[pietre.Z][pietre.R][pietre.T][pietre.S] = l1;
        pietre.S += 1; // backtrack
    }
    
    if (pietre.T > 0){
        f=0;
        pietre.T -= 1;
        l2 = fT(known_l_Z, known_l_R, known_l_T, known_l_S, l+1, pietre);
        if(known_l_T[pietre.Z][pietre.R][pietre.T][pietre.S] < l2) known_l_T[pietre.Z][pietre.R][pietre.T][pietre.S] = l2;
        pietre.T += 1; // backtrack
    }
    
    if(f){ // caso terminale 2
        known_l_S[pietre.Z][pietre.R][pietre.T][pietre.S] = l;
        return l;
    }else{
        known_l_S[pietre.Z][pietre.R][pietre.T][pietre.S] = max(l1, l2);
        return known_l_S[pietre.Z][pietre.R][pietre.T][pietre.S];
    }
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

int max(int a, int b){
    
    if(a>b)
        return a;
    return b;
}


int**** malloc_struttura(stones pietre, int****known_l){
    
    int i, j, k, m;
    
    pietre.Z+=1; pietre.R+=1; pietre.T+=1; pietre.S+=1; // aumento il numero di pietre di 1 in modo da usare il valore in pietre.X come indice e considerare il caso N pietre e/o 0 pietre
    
    known_l = calloc(1, pietre.Z*sizeof(int***));  //allocazione dinamica della struttura che conterrà le soluzioni già calcolate
    for(i=0; i<pietre.Z; i++){
        known_l[i] = calloc(1, pietre.R*sizeof(int**));
        for(j=0; j<pietre.R; j++){
            known_l[i][j] = calloc(1, pietre.T*sizeof(int*));
            for(k=0; k<pietre.T; k++){
                known_l[i][j][k] = calloc(1, pietre.S*sizeof(int));
                for(m=0; m<pietre.S; m++){
                    //****known_l = (int)malloc(sizeof(int));
                    known_l[i][j][k][m] = -1;
                    //printf("%d ", known_l[i][j][k][m]);
                }//printf("\n");
            }//printf("\n");
        }//printf("\n");
    }
    
    return known_l;
}

void free_struttura(int**** known_l, stones pietre){
    
    int i, j, k;
    
    pietre.Z+=1; pietre.R+=1; pietre.T+=1; pietre.S+=1;
    
    for(i=0; i<pietre.Z; i++){
        for(j=0; j<pietre.R; j++){
            for(k=0; k<pietre.T; k++)
                free(known_l[i][j][k]);
            free(known_l[i][j]);
        }
        free(known_l[i]);
    }
    free(known_l);
}
