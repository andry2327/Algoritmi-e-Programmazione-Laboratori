//
//  articolo.c
//  ES_esame
//
//  Created by Andrea Pellegrino on 17/02/21.
//

#include "articolo.h"

struct articoli{
    
    link_art* vett_articoli;
    int N; // numero articoli
};

// relative al tipo articoli

link INITarticoli(int N){
    
    link v_art = malloc(sizeof(*v_art));
    int i;
    
    v_art->N = N;
    v_art->vett_articoli = malloc(N*sizeof(*(v_art->vett_articoli)));
    
    for(i=0; i<N; i++){
        v_art->vett_articoli[i] = INITarticolo();
    }
    
    return v_art;
}

int* INIT_Nart(link articoli, int N){  // memorizza in un vettore il numero di slot dedicati a ciascuna articolo (funge da vettore mark[] prt lr D_rip)
    
    int* curr_N_art = malloc(N*sizeof(*curr_N_art));
    int i;
    
    for(i=0; i<N; i++)
        curr_N_art[i] = GETslot_w(i, articoli);
    
    return curr_N_art;
}

link_art GETarticolo(int x, link articoli){ // *** nel codice di esame ho dimenticato di passare la variabile di tipo 'link'
    return articoli->vett_articoli[x];
}

int GET_Narticoli(link articoli){
    return articoli->N;
}

char* GETrelatore(int x, link articoli){
    return articoli->vett_articoli[x]->relatore;
}

char* GETargomento(int x, link articoli){
    return articoli->vett_articoli[x]->argomento;
}

int GETslot_w(int x, link articoli){
    return GETslot(articoli->vett_articoli[x]);
}

void PRINTarticoli(link articoli){
    
    int i;
    
    for(i=0; i<articoli->N; i++)
        PRINTarticolo(articoli->vett_articoli[i]);
}

void FREEarticoli(link articoli){
    
    int i;
    
    for(i=0; i<articoli->N; i++){
        FREEarticolo(articoli->vett_articoli[i]);
        free(articoli->vett_articoli[i]);
    }
    
    free(articoli->vett_articoli);
    free(articoli);
    
    return;
}





// realtive al tipo articolo

link_art INITarticolo(void){
    
    link_art art;
    
    art = malloc(sizeof(*art));
    
    art->argomento = malloc(sizeof(*art->argomento));
    art->relatore = malloc(sizeof(*art->relatore));
    art->titolo = malloc(sizeof(*art->titolo));
    art->slot = -1;
    
    return art;
}



int GETslot(link_art art){
    return art->slot;
}

void LEGGIarticolo(FILE* fp, link v_art, int i){
    
    fscanf(fp, "%s%s%d%s", v_art->vett_articoli[i]->titolo, v_art->vett_articoli[i]->relatore, &v_art->vett_articoli[i]->slot, v_art->vett_articoli[i]->argomento);
}

void PRINTarticolo(link_art art){
    
    fprintf(stdout, "%s %s %d %s\n", art->titolo, art->relatore, art->slot, art->argomento);
}

void FREEarticolo(link_art art){
    
    free(art->argomento);
    free(art->relatore);
    free(art->titolo);
    
    //free(art);
    
    return;
}
