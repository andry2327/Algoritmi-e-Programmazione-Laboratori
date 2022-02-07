//
//  inv.c
//  E03
//
//  Created by Andrea Pellegrino on 13/12/20.
//

#include "inv.h"

void stat_read(FILE *fp, stat_t *statp){
    
    fscanf(fp, "%d%d%d%d%d%d", &statp->hp, &statp->mp, &statp->atk, &statp->def, &statp->mag, &statp->spr);         //      pg00PG
}

void stat_print(FILE *fp, stat_t *statp, int soglia){
    
    fprintf(fp, "%d %d %d %d %d %d\n", (statp->hp>1)?statp->hp:1, (statp->mp>1)?statp->mp:1, (statp->atk>1)?statp->atk:1, (statp->def>1)?statp->def:1, (statp->mag>1)?statp->mag:1, (statp->spr>1)?statp->spr:1);
}


void inv_read(FILE *fp, inv_t *invp){
    
    fscanf(fp, "%s %s\n", invp->nome, invp->tipo);
}

void inv_print(FILE *fp, inv_t *invp){
    
    fprintf(fp, "%s %s ", invp->nome, invp->tipo);
}


stat_t inv_getStat(inv_t *invp){
    
    return invp->stat;
}
