//
//  articolo.h
//  ES_esame
//
//  Created by Andrea Pellegrino on 17/02/21.
//

#ifndef articolo_h
#define articolo_h

#include <stdio.h>
#include <stdlib.h>

typedef struct articolo* link_art;
typedef struct articoli* link;

struct articolo{
    
    char* titolo;
    char* relatore;
    int slot;
    char* argomento;
};

// relative al tipo articoli

link INITarticoli(int N);
int* INIT_Nart(link articoli, int R);
link_art GETarticolo(int x, link articoli);
int GET_Narticoli(link articoli);
char* GETrelatore(int x, link articoli);
int GETslot_w(int x, link articoli);
void PRINTarticoli(link articoli); // **
char* GETargomento(int x, link articoli); // **
void FREEarticoli(link articoli);


// realtive al tipo articolo

link_art INITarticolo(void);
int GETslot(link_art art);
void LEGGIarticolo(FILE* fp, link v_art, int i); // **
void PRINTarticolo(link_art art); // **
void FREEarticolo(link_art art);

#endif /* articolo_h */
