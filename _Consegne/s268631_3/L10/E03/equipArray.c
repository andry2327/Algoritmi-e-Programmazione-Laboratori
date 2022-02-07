//
//  equipArray.c
//  E03
//
//  Created by Andrea Pellegrino on 13/12/20.
//

#include "equipArray.h"

/* ADT di prima classe collezione di oggetti di equipaggiamento */
struct equipArray_s{
    
    int v_equip[EQUIP_SLOT];
    int in_uso;
};

/* creatore e disruttore */
equipArray_t equipArray_init(void){
    
    int i;
    
    equipArray_t equip = malloc(sizeof *equip);
    equip->in_uso = 0;
    for(i=0; i<EQUIP_SLOT; i++)
    equip->v_equip[i] = -1;
    
    return equip;
}



void equipArray_free(equipArray_t equipArray){
    
    free(equipArray);
}

/* scrittura su file */
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    
    int i;
    int a;
    
    if(equipArray->in_uso>0){
        
        fprintf(fp, "\nCon equipaggiamento:\n");
        
        for(i=0; i<equipArray->in_uso; i++){
        
            a = equipArray_getEquipByIndex(equipArray, invArray, i);
            invArray_printByIndex(fp, invArray, equipArray->v_equip[i]); //non posso stampare direttamente, richiamo una funzione di invArray.h
        }
    }else
        fprintf(fp, "\n*nessun equipaggiamento*\n");
}
/* modifica equipaggiamento scegliendo un oggetto da inventario */
int equipArray_update(equipArray_t equipArray, invArray_t invArray){
    
    int ind; int i;
    int scelta;
    char *s=malloc(sizeof(*s));
    
    printf("seleziona tipo di modifica (1: aggiungi o 2: elimina): ");
    scanf("%d", &scelta);
    
    printf("inserire nome oggetto: ");
    scanf("%s", s);
    
    ind = invArray_searchByName(invArray, s);
    
    if(scelta==1){
        equipArray->v_equip[equipArray->in_uso] = ind;
        equipArray->in_uso += 1;
    }
    else{
        for(i=0; i<equipArray->in_uso; i++)
            if(equipArray->v_equip[i]==ind){
                equipArray->v_equip[i] = -1;
                equipArray->in_uso -= 1;
                break;
            }
    }
    
    free(s);
    
    return ind;
}
/* torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray */
int equipArray_getEquipByIndex(equipArray_t equipArray, invArray_t invArray, int index){
    
    return equipArray->v_equip[index];
}

void equipPg_init (equipArray_t equip){
    
    int i;
    
    for(i=0; i<EQUIP_SLOT; i++)
        equip->v_equip[i] = -1;
    equip->in_uso = 0;
    
    return;
}
