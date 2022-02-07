//
//  ST.c
//  E01
//
//  Created by Andrea Pellegrino on 15/01/21.
//

#include <stdlib.h>
#include <string.h>
#include "ST.h"

typedef struct str* str_p;

struct str{
    char name[30];
};

struct symboltable{
    
    str_p *v_id_str;
    int maxN;
    int size;
};

Edge EDGEcreate(int v, int w, int wt, char type){

    Edge e;
    
    e.v = v;
    e.w = w;
    e.wt = wt;
    e.type = type;
    
    return e;
}

static link node_setNULL(void){
    
    link n = NULL;
    
    return n;
};

link node_INIT(void){
    
    link n = malloc(sizeof(*n));
    
    n->next = node_setNULL();
    n->w = 0;
    n->wt = 0;
    n->type = '\0';
    
    return n;
};

ST STinit(int maxN){
    
    ST st;
    int i;
    
    st = malloc(sizeof(*st));
    st->v_id_str = malloc(maxN*sizeof(*(st->v_id_str)));
    for(i=0; i<maxN; i++)
        st->v_id_str[i] = malloc(sizeof(*st->v_id_str[i]));
    st->maxN = maxN;
    st->size = 0;
    
    return st;
}

void STinsert(ST st, char* s){ // r_elab r_e
        
    strcpy(st->v_id_str[st->size]->name, s); //st->v_r_elab[st->size] = r_e;
    st->size = st->size + 1;
}
 
int ST_search_by_name(char* s, ST st){
    
    int i;
    
    for(i=0; i<st->size; i++){
        if(strcmp(st->v_id_str[i]->name, s)==0){
            return i;
        }
    }
    return -1;
}

char* ST_search_by_index(int key, ST st){
    
    return st->v_id_str[key]->name;
}

int STget_size(ST st){
    
    return st->size;
}

ST ST_ord_by_name(ST st, int dim){
    
    int i, j;
    int swap_f=0;
    char* s;

    for(i=0; i<dim; i++){
        for(j=i+1; j<dim; j++){
            
            if( strcmp(st->v_id_str[j]->name, st->v_id_str[i]->name)<0 )
                swap_f=1;
            
            if(swap_f){
                
                s = st->v_id_str[j]->name;
                st->v_id_str[j] = st->v_id_str[i];
                strcpy(st->v_id_str[i]->name, s);
                swap_f=0;
            }
        }
    }
    
    return st;
}

void STfree(ST st){
    
    free(st->v_id_str);
}

    /*for(k=0; k<dim; k++)
        printf("%s\n", st->v_r_elab[k].id_elab);
    printf("\n");*/
