//
//  personaggi.h
//  E03
//
//  Created by Andrea Pellegrino on 05/12/20.
//

#ifndef personaggi_h
#define personaggi_h
#include "inventario.h"

typedef struct equipaggiamneto{
    
    inventario* in_uso;
    inventario* eqip[8];
    
}equipaggiamento;

typedef struct pg{
    
    char codice[6+1];
    char nome[50+1];
    char classe[50+1];
    equipaggiamento eqip;
    points stats;

}pg;

typedef struct nodePg *link;

typedef struct nodePg{
    
    pg pg_data;
    link pg_next;
    
}nodePg;



link leggi_pg(void);
link new_node_pg(pg pg, link next);
link delete_element(char* s, link h);
link find_pg(char* s, link h, int f); //f=1 se si vuole stampare il personaggio
void add_ogg_pg(char* s, inventario* p, int n_oggetti, link pg);
void delete_ogg_pg(char* s, inventario* p, int n_oggetti, link pg);
void calc_stats_pg (link pg);
void print_list(link p);

#endif /* personaggi_h */
