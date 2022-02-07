//
//  ST.c
//  E03
//
//  Created by Andrea Pellegrino on 23/12/20.
//

#include "ST.h"

struct symboltable{
    
    r_elab *v_r_elab;
    int maxN;
    int size;
};

r_elab r_elab_create(char* e, char* r){
    
    r_elab r_e;
    
    strcpy(r_e.id_elab, e);
    strcpy(r_e.id_rete, r);
    
    return r_e;
}
ST STinit(int maxN){
    
    ST st;
    
    st = malloc(sizeof(*st));
    st->v_r_elab = malloc(sizeof(*st->v_r_elab));
    st->maxN = maxN;
    st->size = 0;
    
    return st;
}

void STinsert(ST st, r_elab r_e){
    
    if(st->size >= st->maxN){
        st->maxN = 2*st->maxN; // raddoppio la capacità disponibile nella tabella di simboli
        st->v_r_elab = realloc(st->v_r_elab, (2*st->maxN)*sizeof(r_elab));
    }
    
    st->v_r_elab[st->size] = r_e;
    st->size++;
}
 
int STsearch_by_name(char* s, ST st){
    
    int i;
    
    for(i=0; i<st->size; i++){
        if(strcmp(st->v_r_elab[i].id_elab, s)==0){
            return i;
        }
    }
    return -1;
}

char* STsearch_by_index(int key, ST st){
    
    return st->v_r_elab[key].id_elab;
}

char* STsearch_by_index_rete(int key, ST st){
    
    return st->v_r_elab[key].id_rete;
}

int STget_size(ST st){
    
    return st->size;
}

ST ST_ord_by_name(ST st, int dim){
    
    int i, j;
    int swap_f=0;
    r_elab temp;

    for(i=0; i<dim; i++){
        for(j=i+1; j<dim; j++){
            
            if( strcmp(st->v_r_elab[j].id_elab, st->v_r_elab[i].id_elab)<0 )
                swap_f=1;
            
            if(swap_f){
                
                temp = st->v_r_elab[j];
                st->v_r_elab[j] = st->v_r_elab[i];
                st->v_r_elab[i] = temp;
                swap_f=0;
            }
        }
    }
    
    return st;
}

void STfree(ST st){
    
    free(st->v_r_elab);
}

    /*for(k=0; k<dim; k++)
        printf("%s\n", st->v_r_elab[k].id_elab);
    printf("\n");*/
