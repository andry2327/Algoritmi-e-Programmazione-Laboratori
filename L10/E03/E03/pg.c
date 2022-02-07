//
//  pg.c
//  E03
//
//  Created by Andrea Pellegrino on 13/12/20.
//

#include "pg.h"

/* lettura e scrittura su file */
int pg_read(FILE *fp, pg_t *pgp){
    
    int f=0;
    
    f = fscanf(fp, "%s %s %s", pgp->cod, pgp->nome, pgp->classe);
    stat_read(fp, &(pgp->b_stat));
    
    if(f!=3)
        return 0;
    
    pgp->equip = equipArray_init(); //inizializzo il vettore dell'equipaggiamento
    pgp->eq_stat.hp=0; pgp->eq_stat.mp=0; pgp->eq_stat.atk=0; pgp->eq_stat.def=0; pgp->eq_stat.mag=0; pgp->eq_stat.spr=0; 
    
    return 1;
}
/* non essendo struct dinamica, pulisce chiamando il distruttire di equipArray */
void pg_clean(pg_t *pgp){
    
    if (pgp->equip!=NULL)
        equipArray_free(pgp->equip);
    
    pgp->equip = NULL;
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    
    fprintf(fp, "%s %s %s ", pgp->cod, pgp->nome, pgp->classe);
    stat_print(fp, &pgp->b_stat, 1);

    equipArray_print(fp, pgp->equip, invArray);
}

void pg_update_stat_Equip(pg_t *pgp, invArray_t invArray, int i){ // modifica i paraemtri dell'equipaggiamento di una personaggio
    
    int f=0, j;
    stat_t* st;
    
    for(j=0; j<EQUIP_SLOT; j++){
        if(equipArray_getEquipByIndex(pgp->equip, invArray, j) == i){ // cioè se l' oggetto è presente nell' inventario del personaggio -> è stato aggiunto
            f=1;
            break;
        }
    }
    
    st = get_stat(invArray, i);
    
    if(f){
        
        pgp->eq_stat.hp += st->hp; pgp->b_stat.hp += st->hp;
        pgp->eq_stat.mp += st->mp; pgp->b_stat.mp += st->mp;
        pgp->eq_stat.atk += st->atk; pgp->b_stat.atk += st->atk;
        pgp->eq_stat.def += st->def; pgp->b_stat.def += st->def;
        pgp->eq_stat.mag += st->mag; pgp->b_stat.mag += st->mag;
        pgp->eq_stat.spr += st->spr; pgp->b_stat.spr += st->spr;
    }else{
        
        pgp->eq_stat.hp -= st->hp; pgp->b_stat.hp -= st->hp;
        pgp->eq_stat.mp -= st->mp; pgp->b_stat.mp -= st->mp;
        pgp->eq_stat.atk -= st->atk; pgp->b_stat.atk -= st->atk;
        pgp->eq_stat.def -= st->def; pgp->b_stat.def -= st->def;
        pgp->eq_stat.mag -= st->mag; pgp->b_stat.mag -= st->mag;
        pgp->eq_stat.spr -= st->spr; pgp->b_stat.spr -= st->spr;
    }
}

/* modifica personaggio aggiungendo/togliendo un equipaggiamento selezionato da inventario:
di fatto e' sufficiente chiamare l'opportuna funzione dal modulo equipArray */
void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    
    int i;
    
    i = equipArray_update(pgp->equip, invArray);
    pg_update_stat_Equip(pgp, invArray, i);
}


