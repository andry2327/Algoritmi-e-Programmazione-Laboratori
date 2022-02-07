//
//  ST.h
//  E01
//
//  Created by Andrea Pellegrino on 15/01/21.
//

#ifndef ST_h
#define ST_h

#include <stdio.h>

typedef struct symboltable *ST;
typedef struct node* link;
typedef struct node_name* name_link;

typedef struct edge{
    
    int v;
    int w;
    char type; // tipologoia dell' arco: back, tree, forward
    int wt;
    
}Edge;

typedef struct node{
    
    int w;
    int wt;
    char type;
    link next;
    
}node;


Edge EDGEcreate(int v, int w, int wt, char type);
link node_INIT(void);
static link node_setNULL(void);

ST STinit(int maxN);
void STfree(ST st);
int STcount(ST st);
void STinsert(ST st, char* s);

void STdisplay(ST st);

int ST_search_by_name(char* s, ST st);
char* ST_search_by_index(int key, ST st);

int STget_size(ST st);
ST ST_ord_by_name(ST st, int dim);

#endif /* ST_h */
