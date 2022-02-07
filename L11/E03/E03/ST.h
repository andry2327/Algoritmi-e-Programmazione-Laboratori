//
//  ST.h
//  E03
//
//  Created by Andrea Pellegrino on 23/12/20.
//

#ifndef ST_h
#define ST_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

typedef struct symboltable *ST;

typedef struct r_elab{
    
    char id_elab[30];
    char id_rete[30];
    
}r_elab;

r_elab r_elab_create(char* e, char* r);

ST STinit(int maxN);
void STfree(ST st);
int STcount(ST st);
void STinsert(ST st, r_elab r_e);

void STdisplay(ST st);

int STsearch_by_name(char* s, ST st);
char* STsearch_by_index(int key, ST st);
char* STsearch_by_index_rete(int key, ST st);
int STget_size(ST st);
ST ST_ord_by_name(ST st, int dim);
 

#endif /* ST_h */
