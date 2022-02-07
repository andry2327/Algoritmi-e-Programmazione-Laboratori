//
//  quotation.c
//  E01
//
//  Created by Andrea Pellegrino on 11/01/21.
//

#include <stdlib.h>
#include "quotation.h"

struct quotation_BST{
    
    q_BST_link root;
    q_BST_link z;
};

struct BST_node{
    
    quotation q;
    q_BST_link L_next;
    q_BST_link R_next;
    int N;
};

BST BSTinit(void){

    BST bst = malloc(sizeof *bst);
    bst->z = NULL;
    bst->root = bst->z;
    
    return bst;
}

int is_different_date(date tmp, date curr_tmp){
    
    if ( ((tmp.year != curr_tmp.year) || (tmp.month != curr_tmp.month) || (tmp.day != curr_tmp.day)) || (curr_tmp.year==0 && curr_tmp.month==0 && curr_tmp.day==0) )
        return 1;
    return 0;
}

double BST_search_by_date(BST bst, q_BST_link next, date date){
    
    if(!is_different_date(next->q.q_date, date))
        return next->q.value;
    
    if(next->L_next != NULL) BST_search_by_date(bst, next->L_next, date);
    if(next->R_next != NULL) BST_search_by_date(bst, next->R_next, date);
    
    return -1;
}

double BST_search_by_date_interval(BST bst, q_BST_link next, date date1, date date2, int M, double *q_M){ // M=0: ricerca del minimo, M=1: ricerca del massimo
    
    if((key_cmp(date1, next->q.q_date)<0 && key_cmp(date2, next->q.q_date)>0) || key_cmp(date2, next->q.q_date)==3){ // controllo se la data corrente è compresa tra le due di riferimento || se le date (con data limite superiore) sono uguali 
        
        if(M==0){ // ricerca del minimo
            
            if(next->q.value < *q_M) *q_M = next->q.value;
            
        }else{ // ricerca del massimo
            
            if(next->q.value > *q_M) *q_M = next->q.value;
        }
    }
    
    if(next->L_next != NULL) BST_search_by_date_interval(bst, next->L_next, date1, date2, M, q_M);
    if(next->R_next != NULL) BST_search_by_date_interval(bst, next->R_next, date1, date2, M, q_M);
    
    return *q_M;
}

int BST_lenght(q_BST_link next, int M){ // M=0: ricerca del minimo, M=1: ricerca del massimo
    
    if(next==NULL)
        return -1;
    
    if(next->L_next==NULL)
        return 1 + BST_lenght(next->R_next, M);
    if(next->R_next==NULL)
        return 1 + BST_lenght(next->L_next, M);
    
    else if(M==1)
        return 1 + max(BST_lenght(next->L_next, M), BST_lenght(next->R_next, M));
    else
        return 1 + min(BST_lenght(next->L_next, M), BST_lenght(next->R_next, M));
}

void BST_print(BST bst, q_BST_link next){
    
    if(next == bst->z)
        return;
    
    BST_print(bst, next->L_next);
    printf("%d/%d/%d: %f\n", next->q.q_date.year, next->q.q_date.month,next->q.q_date.day, next->q.value);
    BST_print(bst, next->R_next);
    
    return;
}

void BST_print_wrapper(BST bst){
    
    BST_print(bst, bst->root);
}

double print_in_data_wrapper(BST bst, date date){
    
    return BST_search_by_date(bst, bst->root, date);
}

double BST_search_by_date_interval_wrapper(BST bst, date date1, date date2, int M){
    
    double *q_M = &bst->root->q.value;
    return BST_search_by_date_interval(bst, bst->root, date1, date2, M, q_M);
}

int BST_lenght_wrapper(BST bst, int M){
    
    return BST_lenght(bst->root, M);
}


q_BST_link rotR(q_BST_link h){
    
    q_BST_link x = malloc(sizeof(*x));
    x = h->L_next;
    h->L_next = x->R_next;
    x->R_next = h;
    
    return x;
}
    
q_BST_link rotL(q_BST_link h){
        
    q_BST_link x = malloc(sizeof(*x));
    x = h->R_next;
    h->R_next = x->L_next;
    x->L_next = h;
    
    return x;
}

q_BST_link partR(q_BST_link h, int r){
    
    int t;
    
    if(h==NULL)
        return h;
    
    if(h->L_next==NULL) t=0;
    else
        t = h->L_next->N;
     
    if(t > r){
        h->L_next = partR(h->L_next, r);
        h = rotR(h);
    }
    if(t < r){
        h->R_next = partR(h->R_next, r-t-1);
        h = rotL(h);
    }
    
    return h;
}
 

static q_BST_link balanceR(q_BST_link h, q_BST_link z, int S){
    
    int r;
    
    if (h == z)
        return z;

    r = (h->N+1)/2-1;

    h = partR(h, r);
    
    if(BST_lenght(h->L_next, 1)/BST_lenght(h->L_next, 0) > S)
        h->L_next = balanceR(h->L_next, z, S);
    if(BST_lenght(h->R_next, 1)/BST_lenght(h->R_next, 0) > S)
        h->R_next = balanceR(h->R_next, z, S);
    
    return h;
}

void BSTbalance(BST bst, int S){
    
    bst->root = balanceR(bst->root, bst->z, S);
}


quotation Qinit(void){

    quotation q;
    
    q.q_date.year=0; q.q_date.month=0; q.q_date.day=0;
    q.value = 0;
    
    return q;
}

double calc_quotatation(int value, int n_title, int* curr_tmp_n_title, double curr_q){
    
    curr_q = curr_q * (*curr_tmp_n_title); // moltiplico la quotazione corrente per il corrente numero di titoli comprati in una determinata data (*curr_tmp_n_title)
    *curr_tmp_n_title += n_title; // aggiorno il numero di titoli comprati in una determinata data (denominatore della nuova media ponderata)
    curr_q = (curr_q + value*n_title)/(*curr_tmp_n_title); // determino il nuovo valore della quoatzione;
    
    return curr_q;
}

static q_BST_link new_BSTnode(quotation x, q_BST_link l, q_BST_link r){ //crea un nuovo nodo del BST
    
    q_BST_link node = malloc(sizeof *node);
    node->q.value = x.value; node->q.q_date.year = x.q_date.year; node->q.q_date.month = x.q_date.month; node->q.q_date.day = x.q_date.day;
    node->L_next = l;
    node->R_next = r;
    node->N = 0;
    
    return node;
}

int key_cmp(date k1, date k2){  //key_cmp() ritorna: 0<n<6 if k1>=k2; 6 if k1==k2; -1 if k1<k2;
    
    if(k1.year == k2.year){
        if(k1.month == k2.month){
            if(k1.day == k2.day){
                if(k1.time.hour == k2.time.hour){
                    if(k1.time.minute == k2.time.minute){
                        return 6;
                    }else
                        if(k1.time.minute > k2.time.minute) return 5;
                }else
                    if(k1.time.hour > k2.time.hour) return 4;
            }else
                if(k1.day >= k2.day) return 3;
        }else
            if(k1.month >= k2.month) return 2;
    }else
        if(k1.year >= k2.year) return 1;
        
    return -1;
}


static q_BST_link insertR(q_BST_link h, quotation x, q_BST_link z){
    
    if (h == z)
        return new_BSTnode(x, z, z);
    
    if(key_cmp(h->q.q_date, x.q_date) >= 1)
        h->L_next = insertR(h->L_next, x, z);
    if(key_cmp(h->q.q_date, x.q_date) == -1)
        h->R_next = insertR(h->R_next, x, z);
 
    (h->N)++; // aumento il numero di nodi nel sottoalbero
    
    return h;
}

void BSTinsert_leafR(BST bst, quotation x){
    
    bst->root = insertR(bst->root, x, bst->z);
}

static void treeFree(q_BST_link h, q_BST_link z){
    
    if (h == z)
        return;
    
    treeFree(h->L_next, z); treeFree(h->R_next, z);
    free(h);
}

void BSTfree(BST bst){
    
    if (bst == NULL)
        return;
    treeFree(bst->root, bst->z);
    free(bst->z);
    free(bst);
}

int max(int a, int b){
    
    if(a>b)
        return a;
    return b;
}

int min(int a, int b){
    
    if(a<b)
        return a;
    return b;
}
