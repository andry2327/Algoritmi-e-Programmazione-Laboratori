//
//  invArray.c
//  E03
//
//  Created by Andrea Pellegrino on 13/12/20.
//

#include "invArray.h"

struct invArray_s{
    
    inv_t* v_inv;
    int dim_v_inv;
};

invArray_t invArray_init(void){
    
    invArray_t inv = malloc(sizeof *inv);
    return inv;
}

void invArray_free(invArray_t invArray){
    
    free(invArray);
}


void invArray_read(FILE *fp, invArray_t invArray){
    
    int n_righe; int i=0;
  
    if(fp==NULL){
        printf("errore apertura file inventario\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp, "%d", &n_righe); invArray->dim_v_inv = n_righe;
    invArray->v_inv = malloc(n_righe*sizeof(*invArray->v_inv));
    
    for(i=0; i<n_righe; i++){
        
        inv_read(fp, invArray->v_inv+i);
        stat_read(fp, &invArray->v_inv[i].stat);
    }
    
    fclose(fp);
}

void invArray_print(FILE *fp, invArray_t invArray){
    
    int i;
  
    if(fp==NULL){
        printf("errore apertura file inventario\n");
        exit(EXIT_FAILURE);
    }
    
    fprintf(fp, "\n");
    
    for(i=0; i<invArray->dim_v_inv; i++){
        
        inv_print(fp, &invArray->v_inv[i]);
        stat_print(fp, &invArray->v_inv[i].stat, 1);
    }
    
    return;
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    
    inv_print(fp, &invArray->v_inv[index]);
    stat_print(fp, &invArray->v_inv[index].stat, 1);
}

inv_t *invArray_getByIndex(invArray_t invArray, int index){
    
    return invArray->v_inv+index;
}

/* ritorna indice (nel vettore) a oggetto selezionato da nome */
int invArray_searchByName(invArray_t invArray, char *name){
    
    int i;
    
    for(i=0; i<invArray->dim_v_inv; i++){
        
        if(strcmp(name, invArray->v_inv[i].nome)==0)
            return i;
    }
    return -1;
}

stat_t* get_stat(invArray_t invArray, int index){ //ritorna le statistiche di un oggetto
    
    return &invArray->v_inv[index].stat ;
}
