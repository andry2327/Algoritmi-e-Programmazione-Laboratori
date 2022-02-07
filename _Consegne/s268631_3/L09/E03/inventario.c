//
//  inventario.c
//  E03
//
//  Created by Andrea Pellegrino on 05/12/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"

inventario* leggi_inv(int* n_oggetti){
    
    FILE* fp_inv;
    int n_righe; int i=0;
    inventario* inv;
 

    fp_inv  = fopen("inventario.txt", "r");
  
    
    if(fp_inv==NULL){
        printf("errore apertura file inventario\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp_inv, "%d", &n_righe); *n_oggetti = n_righe;
    
    inv = malloc(n_righe*sizeof(inventario));
    
    while(fscanf(fp_inv, "%s%s%d%d%d%d%d%d\n", inv[i].nome , inv[i].tipologia,  &inv[i].modificatori.hp, &inv[i].modificatori.mp, &inv[i].modificatori.atk, &inv[i].modificatori.def, &inv[i].modificatori.mag, &inv[i].modificatori.spr) != EOF){
        
        i++;
    }
    
    fclose(fp_inv);
    
    return inv;
}

inventario* find_ogg(char* s, inventario* inv){
    
    int i;
    
    for(i=0; i<8; i++){
        if(strcmp(inv[i].nome , s)==0)
            return inv+i;
    }
    
    return NULL;
}

void print_ogg(inventario* inv){
    
    printf("%s %s %d %d %d %d %d %d\n", inv->nome , inv->tipologia,  inv->modificatori.hp, inv->modificatori.mp, inv->modificatori.atk, inv->modificatori.def, inv->modificatori.mag, inv->modificatori.spr);
}
