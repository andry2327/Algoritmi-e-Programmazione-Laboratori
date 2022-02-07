//
//  programma.c
//  ES_esame
//
//  Created by Andrea Pellegrino on 17/02/21.
//

#include "programma.h"


link_prog INITprogramma(int R, int S){
    
    link_prog pr = malloc(sizeof(*pr));
    int i, j;
    
    pr->R = R;
    pr->S = S;
    
    pr->m_prog = malloc(R*sizeof(*pr->m_prog));
    for(i=0; i<pr->S; i++){
        pr->m_prog[i] = malloc(S*sizeof(*pr->m_prog[i]));
        for(j=0; j<pr->R; j++)
            pr->m_prog[i][j] = -1;
    }
    
    return pr;
}

/*
 
 Formato file programma:
 
 si ripete per R volte nel file (cioè in base a quante sale riunioni ci siano) la seguente struttura
 
 - indice sala riunione
 - S interi (S è in numero di slot) ad indicare l'indice dell'articolo corrispondente in quello slot (-1 se in quello slot non si presenta nessun articolo)
 
 es.
 
 1                // sala riunione 1
 -1 -1 2 2 -1     // L'articolo 2 occupa 2 slot in quel momento della giornata
 2                // sala riunione 2
 3 -1 5 5 5       // L'articolo 3 occupa il primo della giornata, l'articolo 5 occupa 3 slot a fine giornata
 
 ... (ripetuto R volte)
 
 
 */

void LEGGIprogramma(link_prog pr){
    
    char* nome = malloc(sizeof(*nome));
    FILE* fp;
    int i, j, id_r;
    
    printf("inserisci nome file programma: ");
    scanf("%s", nome);
    
    fp = fopen(nome, "r");
    
    for(i=0; i<pr->R; i++){
        fscanf(fp, "%d", &id_r); //printf("%d \n", id_r);
        for(j=0; j<pr->S; j++){
            fscanf(fp, "%d", &pr->m_prog[j][i]);  //printf("%d ", pr->m_prog[j][id_r-1]);
        }
        //printf("\n");
    }
    
    fclose(fp);
               
    return;
}

int CheckProgramma(link_prog pr, link v_art){ // **
    
    int i, j ,k;
    int last_max=0, max;
    int n = GET_Narticoli(v_art);   int* mark = (int*)malloc(n*sizeof(int)); for(i=0; i<n; i++) mark[i]=0;
    char* r = malloc(sizeof(*r));
    
    // verifica che ci siano tutti gli articoli per la quantità di slot previsti
    //PRINTprogramma(pr);
    for(i=0; i<pr->R; i++){
        for(j=0; j<pr->S; j++){
            if(pr->m_prog[j][i] != -1){  //se cella vuota
                
                if(mark[pr->m_prog[j][i]]==1) // se l' articolo è presente più volte
                    return 0;
                
                if(last_max<pr->m_prog[j][i]) last_max = pr->m_prog[j][i]; //**
                
                max = GETslot(GETarticolo(pr->m_prog[j][i], v_art)); //**
                if(max+j > pr->S) //** lo slot dell'articolo è stato spezzato in 2 sale
                    return 0;
                    
                for(k=0; k<max; k++){ //** max sostituito
                    if(pr->m_prog[j+k][i] != pr->m_prog[j][i])// **
                        return 0;
                }
                mark[pr->m_prog[j][i]]=1;
                j += k-1; // ** salto le celle già controllate
            }
        }
    }
    
    if(last_max != GET_Narticoli(v_art)-1) // l'indice maggiore dell' articolo corrisponde al (N di articoli - 1), significa quindi che ci sono tutti gli articoli
        return 0;
    
    // controllo che i relatori non si sovrappongano
    
    for(i=0; i<pr->S; i++){
        for(j=0; j<pr->R; j++){
            if(pr->m_prog[i][j] != -1){
                
            strcpy(r, GETrelatore(pr->m_prog[i][j], v_art)); //r e di tipo char* if(pr->m_prog[i][j]!=-1)  // ** strcpy
            for(k=1; k <= (pr->R - j - 1); k++)
                if((pr->m_prog[i][j+k] != -1) && strcmp(r, GETrelatore(pr->m_prog[i][j+k], v_art))==0) // ** controllo che la cella sia diversda da -1
                    return 0;
            }
        }
    }
    
    for(i=0; i<GET_Narticoli(v_art); i++) // ** controllo ulteriore che siano stati verificati tutti gli articoli e la matrice non contenga solo -1
        if(mark[i]!=1)
            return 0;
    
    
    free(r); free(mark);
    
    return 1;
}

int slot_vuoti(link_prog pr){
    
    int i, j, NV=0;
    
    for(i=pr->S/2; i<pr->S; i++) //considero la "fine della giornata" l'insieme di slot oltre la metà del numero di slot totali
        for(j=0; j<pr->R; j++)
            if(pr->m_prog[i][j]==-1)
                NV++;
    
    return pr->R*pr->S - NV; // NV fino ad adesso erano gli slot vuoti finali, per avere un indice degli slot vuoti iniziali restituisco il complementare di NV
}

int* arg_diversi(link_prog pr, link v_art){
    
    int* NA_i = malloc(pr->R*sizeof(*NA_i));
    int i, j, k, flag=0;
    
    for(i=0; i<pr->R; i++){
        for(j=0; j<pr->S; j++){
            if(pr->m_prog[j][i] != -1){
                for(k=0; k<pr->S-j-1; k++)
                    if(pr->m_prog[j+k][i]!=-1 && pr->m_prog[j+k][i]!=pr->m_prog[j][i]){
                        if( strcmp( GETargomento(pr->m_prog[j][i], v_art), GETargomento(pr->m_prog[j+k][i], v_art) ) == 0)
                            flag=1;
                }
                if(!flag)
                    NA_i[i]++;
            }
        }
    }
    return NA_i;
}

int sum(int* NA_i, link_prog pr){
    
    int i, sum=0;
    
    for(i=0; i<pr->R; i++)
        sum += NA_i[i];
        
    return sum;
}

void copy_sol(link_prog best, link_prog c){
    
    int i, j;
    
    for(i=0; i<c->R; i++)
        for(j=0; j<c->S; j++)
            best->m_prog[j][i] = c->m_prog[j][i];
    PRINTprogramma(best);
    
    return;
}

int Check_curr_N_art(int* curr_N_art, int N_art){ // controlla che gli articoli siano stati inseriri tutti
    
    int i;
    
    for(i=0; i<N_art; i++){
        //printf("%d ", curr_N_art[i]);
        if(curr_N_art[i]!=0){
            //printf("\n\n");
            return 0;
        }
    }
    
    return 1;
}

link_prog D_rip(int pos, int i_art, int* min_somma, link v_art, link_prog curr_prog, link_prog best_prog, int* curr_N_art, int* NA_i, int N_art){
    
    int i, j, k, NV, NA;
    
    if( pos>(curr_prog->R*curr_prog->S) || Check_curr_N_art(curr_N_art, N_art)){
        if(CheckProgramma(curr_prog, v_art)){
            NV = slot_vuoti(curr_prog); // controlla quanti slot vuoti ci sono a fine giornata
            NA_i = arg_diversi(curr_prog, v_art);
            NA = sum(NA_i, curr_prog);
            //PRINTprogramma(curr_prog);
            if(NV+NA < *min_somma){
                copy_sol(best_prog, curr_prog); // copia dei VALORI della mtrice
                *min_somma = NV + NA; //PRINTprogramma(best_prog);
            }
        }
        return best_prog;
    }
    
    for(k=i_art; k<N_art; k++){
        
        i=pos/(curr_prog->R);
        j=pos%(curr_prog->R);
        
        if(curr_N_art[k]>0){
        
            curr_prog->m_prog[j][i] = k; curr_N_art[k]-=1;
            best_prog = D_rip(pos+1, i_art, min_somma, v_art, curr_prog, best_prog, curr_N_art, NA_i, N_art);
            
            curr_prog->m_prog[j][i] = -1; curr_N_art[k]+=1;  // backtrack
            best_prog = D_rip(pos+1, i_art, min_somma, v_art, curr_prog, best_prog, curr_N_art, NA_i, N_art);
        }
    }
    
    return best_prog;
}

void PRINTprogramma(link_prog pr){        //         programma.txt
    
    int i, j;
    
    for(i=0; i<pr->S; i++){
        for(j=0; j<pr->R; j++)
            printf("%d          ", pr->m_prog[i][j]);
        printf("\n");
    }
    
    printf("\n\n");
    
    return;
}
