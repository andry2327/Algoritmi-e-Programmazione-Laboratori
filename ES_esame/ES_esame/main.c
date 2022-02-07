//
//  main.c
//  ES_esame
//
//  Created by Andrea Pellegrino on 17/02/21.
//

#include <stdio.h>
#include <stdlib.h>
#include "programma.h"

link FILEleggi_articoli(link v_art);

int main(int argc, const char * argv[]){
    
    int R = atoi(argv[1]), S = atoi(argv[2]);
    link v_art = NULL;
    link_prog pr = INITprogramma(R, S);
    link_prog best_prog = INITprogramma(R, S);
    link_prog curr_prog = INITprogramma(R, S);
    int cmd;
    int* curr_N_art;
    int* NA_i = malloc(R*sizeof(*NA_i));
    int min = R*R*S*S; // valore fittizio iniziale 
    
    v_art = FILEleggi_articoli(v_art);
    
    /* questa parte non è chiesta, è implementata solo per utilià*/
    while(1){
        printf("1. leggi programma\n2. Check programma\n3.Ottimizzazione\ncomando: ");
        scanf("%d", &cmd);
        
        if(cmd==1){
            LEGGIprogramma(pr);
            PRINTprogramma(pr);
        
        }else if(cmd==2){
            if(CheckProgramma(pr, v_art))       //    programma.txt
                printf("Il programma è valido\n\n");
            else
                printf("Il programma non è valido\n\n");
        }else if(cmd==3){
            curr_N_art = INIT_Nart(v_art, GET_Narticoli(v_art));
            best_prog = D_rip(0, 0, &min, v_art, curr_prog, best_prog, curr_N_art, NA_i, GET_Narticoli(v_art));
            PRINTprogramma(best_prog);
            
        }else if(cmd==-1){
            FREEarticoli(v_art);
            exit(EXIT_SUCCESS);
        }
            
    }
    /*    **********************************************    */
    
   
    
    return 0;
}

link FILEleggi_articoli(link v_art){
    
    FILE* fp;
    int N;
    int i;
    
    fp=fopen("articoli.txt", "r");
    
    if(fp==NULL){
        printf("errore apertura file\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp, "%d", &N);
    v_art = INITarticoli(N);

    for(i=0; i<N; i++)
        LEGGIarticolo(fp, v_art, i);
    
    //PRINTarticoli(v_art);
    fclose(fp);
    
    return v_art;
}
