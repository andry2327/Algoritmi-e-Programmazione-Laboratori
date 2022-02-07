//
//  main.c
//  E02
//
//  Created by Andrea Pellegrino on 21/12/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_DIAG 5
#define N_DIAG 3

typedef struct elem *elem_p;

typedef struct elem{
    
    char nome[100+1];
    int tipologia;
    int dir_in;
    int dir_out;
    int req_prec;
    int finale;
    float valore;
    int difficoltà;
    float rapp_val_diff;
}elem;

typedef struct diag{
    
    elem_p v_elem[MAX_DIAG];
    int diff_diag;
    float val_diag;
    int q_es; //quantità di esercizi
}diag;

typedef struct esercizio{
    
    diag d[N_DIAG];
    int diff_es;
    float val_es;
}esercizio_t;

esercizio_t* init_esercizio(esercizio_t *es);
elem* file_read(int *n, elem *elementi);
elem* ord_by_rapp(int n, elem *elementi);
int D_rip(int pos, int i_d, elem *el, esercizio_t *sol, esercizio_t *sol_MAX, int DD, int DP, int n, int f);

int is_prec_comp(diag d, elem el);
int is_start(elem el);
int is_fin(elem el);
int is_elem_ac_in_d(esercizio_t *es);
int is_AvInd_in_es(esercizio_t *es);
int is_elem_acc_seq(esercizio_t *es);
int is_el_fin_maj8(esercizio_t *es);
int is_diff_d_valid(elem el, diag d, int DD);
int is_diff_max_valid(esercizio_t *es, int DP);

void cpy_elem_in_sol(esercizio_t *sol, esercizio_t *sol_MAX);

int main(int argc, const char * argv[]) {
    
    int DD, DP;
    int i, j;
    int n_righe;
    elem *elementi=NULL;
    esercizio_t *sol = NULL; sol = init_esercizio(sol);
    esercizio_t *sol_MAX = NULL; sol_MAX = init_esercizio(sol_MAX);
    
    elementi = file_read(&n_righe, elementi);
    elementi = ord_by_rapp(n_righe, elementi); int k;  // ordino gli elementi in ordine crescente in base al rapoorto valore/diffcoltà
    
    for(k=0; k<n_righe; k++)
        printf("%s  %.2f  %d      %.2f\n", elementi[k].nome, elementi[k].valore, elementi[k].difficoltà, elementi[k].rapp_val_diff);
    printf("\n");
    
    while(1){

        printf("inserisci difficoltà max diagonale e difficoltà max complessiva (oppre 'exit' per temrinare): ");
    
        if(scanf("%d%d", &DD, &DP)!=2)
            exit(EXIT_SUCCESS);
        else{
            
            printf("-----test con DD = %d, DP = %d:\n\n", DD, DP);
            
            if(D_rip(0, 0, elementi, sol, sol_MAX, DD, DP, n_righe, 0)){
                
                printf("punteggio TOT: %f, difficoltà: %d\n\n", sol_MAX->val_es, sol_MAX->diff_es);
                for(i=0; i<N_DIAG; i++){
                    printf("difficoltà diagonale %d: %d\n", i, sol_MAX->d[i].diff_diag);
                    for(j=0; j<sol_MAX->d[i].q_es; j++)
                        printf("%s ", sol_MAX->d[i].v_elem[j]->nome);
                    printf("\n");
                }
                printf("-----\n\n");
            }
        }
    }
    
}

elem* file_read(int *n, elem *elementi){
    
    FILE* fp;
    int i;
    
    fp = fopen("elementi.txt", "r");
    
    if(fp==NULL){
        printf("errore apertura file");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp, "%d", n);
    elementi = malloc((*n)*sizeof(*elementi));
    
    for(i=0; i<*n; i++){
        fscanf(fp, "%s%d%d%d%d%d%f%d", elementi[i].nome, &elementi[i].tipologia, &elementi[i].dir_in, &elementi[i].dir_out, &elementi[i].req_prec, &elementi[i].finale, &elementi[i].valore, &elementi[i].difficoltà);
        elementi[i].rapp_val_diff = elementi[i].valore/elementi[i].difficoltà;
    }
    
    fclose(fp);
    
    return elementi;
}

elem* ord_by_rapp(int n, elem *elementi){
    
    elem temp;
    int i, j;
    int swap_f=0;

    for(i=0; i<n; i++){
        for(j=i+1; j<n; j++){
            
            if(elementi[j].rapp_val_diff > elementi[i].rapp_val_diff)
                swap_f=1;
            
            if(swap_f){
                
                temp = elementi[j];
                elementi[j] = elementi[i];
                elementi[i] = temp;
                swap_f=0;
            }
        }
    }
    
    return elementi;
}

int D_rip(int pos, int i_d, elem *el, esercizio_t *sol, esercizio_t *sol_MAX, int DD, int DP, int n, int f){
    
    int i; int p; int d_index = 0, pos_d;
    
    if( (pos >= (MAX_DIAG*N_DIAG)) || ((i_d>=19) && (pos/MAX_DIAG>=3))){
        if( is_AvInd_in_es(sol) && is_elem_ac_in_d(sol) && is_elem_acc_seq(sol) && is_diff_max_valid(sol, DP) ){
            if(is_el_fin_maj8(sol)){
                
                p = sol->d[2].val_diag; sol->d[2].val_diag = p*1.5;
                sol->val_es += (-p + p*1.5); // -> += 0.5*p
            }
        
            if(sol->val_es > sol_MAX->val_es){
                cpy_elem_in_sol(sol, sol_MAX);
                f=1;
            }
        }
        return f;
    }
    
    d_index = pos/MAX_DIAG; // indica la diagonale 1, 2 o 3 (cioe in posizione 0, 1 o 2)
    pos_d = pos%MAX_DIAG; // posizione nella diagonale
    
    for(i_d=i=0; i<n; i++, i_d++){
         
        if(pos_d==0){
            if(is_start(el[i])){
                
                sol->d[d_index].v_elem[0] = &el[i];
                
                sol->d[d_index].q_es += 1;
                sol->d[d_index].diff_diag += el[i].difficoltà;
                sol->d[d_index].val_diag += el[i].valore;
                sol->val_es += sol->val_es;
                
                f = D_rip(pos+1, i_d, el, sol, sol_MAX, DD, DP, n, f);
                
                sol->d[d_index].v_elem[0] = NULL;
                
                sol->d[d_index].q_es -= 1;
                sol->d[d_index].diff_diag -= el[i].difficoltà;
                sol->d[d_index].val_diag -= el[i].valore;
                sol->val_es -= sol->val_es;
                
            }
        }
        else if( is_prec_comp(sol->d[d_index], el[i]) && is_diff_d_valid(el[i], sol->d[d_index], DD) ){
            
            sol->d[d_index].v_elem[pos_d] = el+i;
            
            sol->d[d_index].q_es += 1;
            sol->d[d_index].diff_diag += el[i].difficoltà;
            sol->d[d_index].val_diag += el[i].valore;
            sol->val_es += sol->val_es;
            
            f = D_rip(pos+1, i_d, el, sol, sol_MAX, DD, DP, n, f);
            
            sol->d[d_index].v_elem[pos_d] = NULL;
            
            sol->d[d_index].q_es -= 1;
            sol->d[d_index].diff_diag -= el[i].difficoltà;
            sol->d[d_index].val_diag -= el[i].valore;
            sol->val_es -= sol->val_es;
        }
    } // fine for()
    
    pos += MAX_DIAG - sol->d[d_index].q_es; // aumento pos per la diagonale successiva: nella d corrente non è possibile mettere altri elementi

    f = D_rip(pos, i_d, el, sol, sol_MAX, DD, DP, n, f);
    
    return f;
}

/*
for(k=0; k<n; k++)
    printf("%s %f %d %f\n", elementi[k].nome, elementi[k].rapp_val_diff);
printf("\n");
*/

void cpy_elem_in_sol(esercizio_t *sol, esercizio_t *sol_MAX){
    
    int i, j;
    
    for(i=0; i<N_DIAG; i++){
        for(j=0; j<sol->d[i].q_es; j++){
        
            strcpy(sol_MAX->d[i].v_elem[j]->nome, sol->d[i].v_elem[j]->nome);
            sol_MAX->d[i].v_elem[j]->tipologia = sol->d[i].v_elem[j]->tipologia;
            sol_MAX->d[i].v_elem[j]->dir_in = sol->d[i].v_elem[j]->dir_in;
            sol_MAX->d[i].v_elem[j]->dir_out = sol->d[i].v_elem[j]->dir_out;
            sol_MAX->d[i].v_elem[j]->req_prec = sol->d[i].v_elem[j]->req_prec;
            sol_MAX->d[i].v_elem[j]->finale = sol->d[i].v_elem[j]->finale;
            sol_MAX->d[i].v_elem[j]->valore = sol->d[i].v_elem[j]->valore;
            sol_MAX->d[i].v_elem[j]->difficoltà = sol->d[i].v_elem[j]->difficoltà;
            sol_MAX->d[i].v_elem[j]->rapp_val_diff = sol->d[i].v_elem[j]->rapp_val_diff;
        }
        
        
        sol_MAX->d[i].q_es = sol->d[i].q_es;
        sol_MAX->d[i].diff_diag = sol->d[i].diff_diag;
        sol_MAX->d[i].val_diag = sol->d[i].val_diag;
    }
    
    sol_MAX->val_es = sol->val_es;
}

int is_elem_ac_in_d(esercizio_t *es){
    
    int i, j;
    
    for(i=0; i<N_DIAG; i++)
        for(j=0; j<es->d[i].q_es; j++)
            if((es->d[i].v_elem[j]->tipologia == 1) || (es->d[i].v_elem[j]->tipologia == 2))
                return 1;
    return 0;
}

int is_AvInd_in_es(esercizio_t *es){
    
    int i, j;
    int f_av=0, f_ind=0;
    
    for(i=0; i<3; i++)
        for(j=0; j<es->d[i].q_es; j++){
            
            if(es->d[i].v_elem[j]->tipologia == 2)
                f_av=1;
            if(es->d[i].v_elem[j]->tipologia == 1)
                f_ind=1;
            
            if(f_av && f_ind)
                return 1;
    }
    return 0;
}

int is_elem_acc_seq(esercizio_t *es){
    
    int i, j;
    
    for(i=0; i<3; i++)
        for(j=0; j<es->d[i].q_es-1; j++){
            
            if((es->d[i].v_elem[j]->tipologia == 1) || (es->d[i].v_elem[j]->tipologia == 2))
                if((es->d[i].v_elem[j+1]->tipologia == 1) || (es->d[i].v_elem[j+1]->tipologia == 2))
                    return 1;
    }
    return 0;
}

int is_el_fin_maj8(esercizio_t *es){
    
    int f = es->d[2].q_es - 1; if(f==-1) return 0;
    
    if(es->d[2].v_elem[f]->difficoltà >= 8)
        return 1;
    return 0;
}

int is_prec_comp(diag d, elem el){
    
    int f = d.q_es - 1;
    
    if(el.dir_in == d.v_elem[f]->dir_out)
        return 1;
    return 0;
        
}

int is_start(elem el){
    
    if(el.req_prec==0 && el.dir_in==1)
        return 1;
    return 0;
}

int is_fin(elem el){
    
    if(el.finale==1)
        return 1;
    return 0;
}

int is_diff_d_valid(elem el, diag d, int DD){  // controlla se l'elemento che sto per inserire non faccia superqare la diddicoltà max per la diagonale
    
    if((d.diff_diag + el.difficoltà) > DD)
        return 0;
    return 1;
}

int is_diff_max_valid(esercizio_t *es, int DP){
    
    if(es->diff_es <= DP)
        return 1;
    return 0;
}

esercizio_t* init_esercizio(esercizio_t *es){
    
    int i, j;
    
    es = malloc(sizeof(*es));
    
    
    for(i=0; i<N_DIAG; i++){
        for(j=0; j<MAX_DIAG; j++){
            es->d[i].v_elem[j] = malloc(sizeof(*es->d[i].v_elem[j]));
            es->d[i].v_elem[j]->difficoltà = 0;
            es->d[i].v_elem[j]->dir_in = 0;
            es->d[i].v_elem[j]->dir_out = 0;
            es->d[i].v_elem[j]->finale = 0;;
            es->d[i].v_elem[j]->rapp_val_diff = 0;
            es->d[i].v_elem[j]->req_prec = 0;
            es->d[i].v_elem[j]->tipologia = 0;
            es->d[i].v_elem[j]->valore = 0;
        }
        es->d[i].q_es = 0;
        es->d[i].val_diag = 0;
        es->d[i].diff_diag = 0;
    }
    
    return es;
}
