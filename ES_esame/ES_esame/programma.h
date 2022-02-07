//
//  programma.h
//  ES_esame
//
//  Created by Andrea Pellegrino on 17/02/21.
//

#ifndef programma_h
#define programma_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "articolo.h"

typedef struct programma* link_prog;

struct programma{
    
    int** m_prog;  // L'intero indica la posizione nel vettore vett_articoli[], in cui sono presenti tutte le info di un articolo, la matrice è grande RxS
    int R;
    int S;
};

link_prog INITprogramma(int R, int S);
void LEGGIprogramma(link_prog pr);
int CheckProgramma(link_prog pr, link v_art);
link_prog D_rip(int pos, int i_art, int* min_somma, link v_art, link_prog curr_prog, link_prog best_prog, int* curr_N_art, int* NA_i, int N_art);
void PRINTprogramma(link_prog pr);
void copy_sol(link_prog best, link_prog c);
int Check_curr_N_art(int* curr_N_art, int N_art);

#endif /* programma_h */
