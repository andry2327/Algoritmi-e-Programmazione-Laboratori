//
//  personaggi.c
//  E03
//
//  Created by Andrea Pellegrino on 05/12/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"
#include "personaggi.h"

link leggi_pg(void){
    
    FILE* fp_pg;
    pg tmp;
    link head = malloc(sizeof(*head)); head->pg_next=NULL;
    
    fp_pg  = fopen("pg.txt", "r");
  
    if(fp_pg==NULL){
        printf("errore apertura file personaggi\n");
        exit(EXIT_FAILURE);
    }
    
    while(fscanf(fp_pg, "%s%s%s%d%d%d%d%d%d\n", tmp.codice, tmp.nome, tmp.classe, &tmp.stats.hp, &tmp.stats.mp, &tmp.stats.atk, &tmp.stats.def, &tmp.stats.mag, &tmp.stats.spr) != EOF){
        
        head->pg_next = new_node_pg(tmp, head->pg_next);
    }
    
    fclose(fp_pg);
    
    return head->pg_next;
}

link new_node_pg(pg pg, link next){
    
    link x = malloc(sizeof(*x)); x->pg_next=NULL; int i;
    
    if(x==NULL){
        return NULL;
    }
    
    x->pg_next = next;  //inserzione in testa
    x->pg_data = pg;    //
    
    x->pg_data.eqip.in_uso=NULL ;
    for(i=0; i<8; i++){
        x->pg_data.eqip.eqip[i]=NULL;
    }
    
    return x;
}

link delete_element(char* s, link h){
    
    link x = NULL, p = NULL;
    
    for(x=h->pg_next, p=h; (x!=NULL) && (strcmp(s, x->pg_data.codice)!=0); p=x, x=x->pg_next);
    
    p->pg_next = x->pg_next;
   
    return x;
}

link find_pg(char* s, link h, int f){  //f=1 se si vuole stampare il personaggio
    
    link x = NULL, p = NULL;
    
    for(x=h->pg_next, p=h; (x!=NULL) && (strcmp(s, x->pg_data.codice)!=0); p=x, x=x->pg_next);
    
    if(f==1)
        printf("%s %s %s %d %d %d %d %d %d\n", x->pg_data.codice,  x->pg_data.nome,  x->pg_data.classe,  x->pg_data.stats.hp ,  x->pg_data.stats.mp,  x->pg_data.stats.atk,  x->pg_data.stats.def, x->pg_data.stats.mag, x->pg_data.stats.spr);
    
    return x;
}

void add_ogg_pg(char* s, inventario* p, int n_oggetti, link pg){
    
    int i; inventario* p1=NULL; int flag = 1;
    
    for(i=0; (i<n_oggetti) && (flag); i++){
        if(strcmp(p[i].nome, s)==0){
            p1 = &p[i];
            flag = 0;
        }
    }
    
    flag=1;
        
    for(i=0; (i<8) && flag; i++){
        if(pg->pg_data.eqip.eqip[i] == NULL){
            pg->pg_data.eqip.eqip[i] = p1;
            printf("\nElemento %s aggiunto all' inventario di %s, equipaggiamento attuale:\n", s, pg->pg_data.nome);
            flag = 0;
        }else if(strcmp(pg->pg_data.eqip.eqip[i]->nome, s)==0){
            printf("\noggetto già esistente nell'inventario di %s\n", pg->pg_data.nome);
            return ;
        }
    }
}

void delete_ogg_pg(char* s, inventario* p, int n_oggetti, link pg){
    
    int i; int flag = 1;
    
    for(i=0; (i<n_oggetti) && flag; i++){
        if(strcmp(pg->pg_data.eqip.eqip[i]->nome, s) == 0){
            pg->pg_data.eqip.eqip[i] = NULL;
            printf("\nElemento %s cancellato dall' inventario di %s, equipaggiamento attuale:\n", s, pg->pg_data.nome);
            flag = 0;
        }
    }
    
    if(flag==1){
        printf("\noggetto da cancellare non trovato\n");
    }
}

void calc_stats_pg (link pg){
    
    int st[6];
    int i=0;
    inventario* x;
    
    st[0] = pg->pg_data.stats.hp;
    st[1] = pg->pg_data.stats.mp;
    st[2] = pg->pg_data.stats.atk;
    st[3] = pg->pg_data.stats.def;
    st[4] = pg->pg_data.stats.mag;
    st[5] = pg->pg_data.stats.spr;
    
    for(x=pg->pg_data.eqip.eqip[i]; x!=NULL; x=pg->pg_data.eqip.eqip[i]){
        
        st[0] += x->modificatori.hp;
        st[1] += x->modificatori.mp;
        st[2] += x->modificatori.atk;
        st[3] += x->modificatori.def;
        st[4] += x->modificatori.mag;
        st[5] += x->modificatori.spr;
        
        i++;
    }
    printf("\n");
    
    printf("statistiche di %s:\n\n", pg->pg_data.nome);
    
    printf("hp: %d\n", (st[0]<0)?0:st[0]);
    printf("mp: %d\n", (st[1]<0)?0:st[1]);
    printf("atk: %d\n", (st[2]<0)?0:st[2]);
    printf("def: %d\n", (st[3]<0)?0:st[3]);
    printf("mag: %d\n", (st[4]<0)?0:st[4]);
    printf("spr: %d\n", (st[5]<0)?0:st[5]);
    
    printf("\n\n");
}

void print_list(link PgList_head){
    
    link p = malloc(sizeof(link));
    
    for(p = PgList_head->pg_next; p!=NULL; p=p->pg_next){
        printf("%s %s %s %d %d %d %d %d %d\n", p->pg_data.codice, p->pg_data.classe , p->pg_data.nome, p->pg_data.stats.hp, p->pg_data.stats.mp, p->pg_data.stats.atk, p->pg_data.stats.def, p->pg_data.stats.mag,p->pg_data.stats.spr);
    }
}
