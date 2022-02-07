//
//  pgList.c
//  E03
//
//  Created by Andrea Pellegrino on 13/12/20.
//

#include "pgList.h"

struct pgList_s{
    
    pg_t pg_data;
    pgList_t pg_next;
};

/* creatore e distruttore */
pgList_t pgList_init(void){
    
    pgList_t head = malloc(sizeof(*head));
    head->pg_next=NULL;
    
    return head;
}

void pgList_free(pgList_t pgList){
    
    if(pgList->pg_next==NULL){
        free(pgList);
        return;
    }
        
    pgList_free(pgList->pg_next);
}

/* lettura e scrittura su file */
void pgList_read(FILE *fp, pgList_t pgList){
    
    pg_t pg;
    
    while(pg_read(fp, &pg)==1){
        
        pgList_insert(pgList, pg);
    }
    return;
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    
    pgList_t x;
    
    for(x=pgList->pg_next; x!= NULL; x=x->pg_next){
        
        printf("\n");
        pg_print(fp, &x->pg_data, invArray);
        printf("\n");
    }
}

/* inserimento di un nuovo personaggio */
void pgList_insert(pgList_t pgList, pg_t pg){
    
    pgList_t x = malloc(sizeof(*x)); x->pg_next=NULL;
    
    if(x==NULL)
        return;
    
    x->pg_next = pgList->pg_next;
    pgList->pg_next = x;      //inserzione in testa
    x->pg_data = pg;          //
    
    equipPg_init(x->pg_data.equip);
    
    return;
}
/* cancellazione con rimozione */
void pgList_remove(pgList_t pgList, char* cod){
    
    pgList_t x = NULL, p = NULL;
    pg_t* pg_del;
    
    pg_del = pgList_searchByCode(pgList, cod);
    
    for(x=pgList->pg_next, p=pgList; (x!=NULL) && (&x->pg_data != pg_del); p=x, x=x->pg_next);
    
    p->pg_next = x->pg_next;
    
    return;
}
/* ricerca per codice, ritornando il puntatore */
pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    
    pgList_t x = NULL, p = NULL;
    
    for(x=pgList->pg_next, p=pgList; (x!=NULL) && (strcmp(cod, x->pg_data.cod)!=0); p=x, x=x->pg_next);
    
    return &x->pg_data;
}
