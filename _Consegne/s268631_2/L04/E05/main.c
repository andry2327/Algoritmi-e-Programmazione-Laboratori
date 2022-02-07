//
//  main.c
//  E04
//
//  Created by Andrea Pellegrino on 28/10/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_R 1000
#define MAX_DIM 30

typedef struct tratta{
    
    char codice [MAX_DIM+1];
    char partenza [MAX_DIM+1];
    char destinazione [MAX_DIM+1];
    char data [MAX_DIM+1];
    char ora_partenza [MAX_DIM+1];
    char ora_arrivo [MAX_DIM+1];
    int ritardo;
    
}tratta;

char* key(tratta corse[MAX_R], int ord, int i);

void init_str(char s[31]);
int command_selector(char command[31]);
void ord_by_data(tratta v_ord_by_data[MAX_R], int n_righe);
void ord_by(tratta v_ord_by[MAX_R], int n_righe, int ord_state);

void ricerca(char comando[31], struct tratta corse[MAX_R], tratta v_ord_by_data[MAX_R], int n_righe);
void ricerca_lin(char comando[31], struct tratta corse[MAX_R], int n_righe);
void ricerca_dic(char comando[31], tratta v_ord_by_data[MAX_R], int n_righe);

int data_to_num(char data[11]);
int time_to_sec(char data[9]);

void print_log(struct tratta corse[MAX_R], int n_righe);

int main(int argc, const char * argv[]) {
    
    FILE* fp;
    char comando[31];
    int num_righe;
    int i;
   // int order_state=0, *p_ord_state=&order_state; // indica se il vett di struct è ordinato e con quale ordinamento (in base al return di command_selector() ,es. ord_by_stazione_p = 4)
    tratta corse[MAX_R];
    tratta v_ord_by_data[MAX_R];
    tratta v_ord_by_codice[MAX_R];
    tratta v_ord_by_partenza[MAX_R];
    tratta v_ord_by_arrivo[MAX_R];
    
    fp = fopen("log.txt", "r");
    
    if (fp == NULL){
        printf("errore aperura file 'log.txt'\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp, "%d\n", &num_righe);
    
    for(i=0; i<num_righe; i++)
        fscanf(fp, "%s %s %s %s %s %s %d", corse[i].codice, corse[i].partenza, corse[i].destinazione, corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, &corse[i].ritardo);
    
    //inizializzazione
    
    for(i=0; i<num_righe; i++){
        
        v_ord_by_data[i] = corse[i];
        v_ord_by_codice[i] = corse[i];
        v_ord_by_partenza[i] = corse[i];
        v_ord_by_arrivo[i] = corse[i];
    }
        
    
    //ordinamenti
    
    ord_by_data(v_ord_by_data, num_righe);
    ord_by(v_ord_by_codice, num_righe, 3);  //ord by codice
    ord_by(v_ord_by_partenza, num_righe, 4);  //ord by partenza
    ord_by(v_ord_by_arrivo, num_righe, 5);  // ord by arrivo
    
    while(1){
    
        printf("Inserisci comando da eseguire:\n");
        printf("stampa_log / ord_by_data /  ord_by_codice /  ord_by_stazione_p /  ord_by_stazione_a / ricerca / termina \n");
        scanf("%s", comando);
    
        switch(command_selector(comando)){
            
            case 1:
                print_log(corse, num_righe); break;
            
            case 2:  //ord by data
                print_log(v_ord_by_data, num_righe); break;
            
            case 3:  //ord by codice
                print_log(v_ord_by_codice, num_righe); break;
                
            case 4:  //ord by partenza
                print_log(v_ord_by_partenza, num_righe); break;
                    
            case 5:  // ord by arrivo
                print_log(v_ord_by_arrivo, num_righe); break;
                            
            case 6:
                printf("inserisci nome stazione:\n");
                scanf("%s", comando);
                printf("\n");
                ricerca(comando, corse, v_ord_by_partenza, num_righe);
                break;
            
            case 0:
                exit(EXIT_SUCCESS);
        
            default: printf("comando errato\n");
        }
    }
    
    return 0;
}

void init_str(char s[31]){
    
    int i;
    
    for(i=0; i<5; i++)
        s[i] = '\0';
}

int command_selector(char command[30]){
    
    if(strcmp(command, "stampa_log")==0)
        return 1;
    if(strcmp(command, "ord_by_data")==0)
        return 2;
    if(strcmp(command, "ord_by_codice")==0)
        return 3;
    if(strcmp(command, "ord_by_stazione_p")==0)
        return 4;
    if(strcmp(command, "ord_by_stazione_a")==0)
        return 5;
    if(strcmp(command, "ricerca")==0)
        return 6;
    if(strcmp(command, "termina")==0)
        return 0;
    
    return -1;
}

void print_log(struct tratta corse[MAX_R], int n_righe){
    
    int i;
    
    printf("\n");
    for(i=0; i<n_righe; i++)
        printf("%s %s %s %s %s %s %d\n", corse[i].codice, corse[i].partenza, corse[i].destinazione, corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, corse[i].ritardo);
    printf("\n");
    
}

void ord_by_data(tratta v_ord_by_data[MAX_R], int n_righe){ //utilizza un algoritmo di Bubble Sort (stabile)
    
    int i, j;
    int n_j1, n_j2;
    int swap_f=0;
    tratta temp;
    
    for(i=0; i<n_righe-1; i++){
        for(j=0; j<n_righe-i-1; j++){
            
            n_j1 = data_to_num(v_ord_by_data[j].data);
            n_j2 = data_to_num(v_ord_by_data[j+1].data);
            
            if(n_j1 > n_j2)
                swap_f=1;

            else if(n_j1 == n_j2){
                if (time_to_sec(v_ord_by_data[j].partenza) > time_to_sec(v_ord_by_data[j+1].partenza))
                    swap_f=1;
            }
            if(swap_f){
                
                temp = v_ord_by_data[j];
                v_ord_by_data[j] = v_ord_by_data[j+1];
                v_ord_by_data[j+1] = temp;
                swap_f=0;
            }
        }
    }
}

void ord_by(tratta v_ord_by[MAX_R], int n_righe, int ord_state){  //serve per ordinare in base al codice, partenza e arrivo, grazier a *p_order_state e la funzione key()
    
    int i, j;
    int swap_f=0;
    char s_j1[MAX_DIM+1], s_j2[MAX_DIM+1];
    tratta temp;
    
    for(i=0; i<n_righe-1; i++){
        for(j=0; j<n_righe-i-1; j++){
            
            strcpy(s_j1, key(v_ord_by, ord_state, j));
            strcpy(s_j2, key(v_ord_by, ord_state, j+1));
            
            if(strcmp(s_j1, s_j2) > 0)
                swap_f=1;
            
            if(swap_f){
                
                temp = v_ord_by[j];
                v_ord_by[j] = v_ord_by[j+1];
                v_ord_by[j+1] = temp;
                swap_f=0;
            }
        }
    }
}

void ricerca(char comando[31], struct tratta corse[MAX_R], tratta v_ord_by_data[MAX_R], int n_righe){  // mantengo entrambi i tipi di ricerca per visulazizzare casi multipli ma sfruttare anche                                                                                                                          // l' efficenza della ricerca dicotomica
    printf("Risultati (ricerca dicotomica):");
    ricerca_dic(comando, v_ord_by_data, n_righe); // se ci sono corrispondenze multiple, ne viene stampata solo una di esse
    printf("Risultati (ricerca lineare):");
    ricerca_lin(comando, corse, n_righe);
}

void ricerca_lin(char comando[31], struct tratta corse[MAX_R], int n_righe){
    
    int i, found=0;
    
    printf("\n");
    for(i=0; i<n_righe; i++){
        if( strncmp(comando, corse[i].partenza, strlen(comando))==0 ){
            printf("%s %s %s %s %s %s %d\n", corse[i].codice, corse[i].partenza, corse[i].destinazione, corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, corse[i].ritardo);
            found = 1;
        }
    }
    if(!found)
        printf("nessuna corrispondenza trovata\n");
        
    printf("\n");
}

void ricerca_dic(char comando[31], tratta v_ord_by_data[MAX_R], int n_righe){
    
    printf("\n");
    
    if( strncmp(comando, v_ord_by_data[n_righe/2].partenza, strlen(comando))==0 )
        printf("%s %s %s %s %s %s %d\n", v_ord_by_data[n_righe/2].codice, v_ord_by_data[n_righe/2].partenza, v_ord_by_data[n_righe/2].destinazione, v_ord_by_data[n_righe/2].data, v_ord_by_data[n_righe/2].ora_partenza, v_ord_by_data[n_righe/2].ora_arrivo, v_ord_by_data[n_righe/2].ritardo);
    else{
        
        if( strncmp(comando, v_ord_by_data[n_righe/2].partenza, strlen(comando))<0 ){
            ricerca_dic(comando, v_ord_by_data, n_righe/2);
        }else{
            ricerca_dic(comando, v_ord_by_data+(n_righe/2), n_righe-(n_righe/2));
        }
    }

    printf("\n");
}


int data_to_num(char data[11]){ // questa funzione converte la data in un numero pari a anno*365 + mese*30 + giorno, per poter operare confronti (< o >) tra date in seguito
    
    int anno=0, mese=0, giorno=0;
    int i=0;
    char temp[5];
    
    while(i<4){
        
        temp[i] = data[i];
        i++;
    }
    anno = atoi(temp);
    
    init_str(temp); i=0;
    
    while(i<2){
        
        temp[i] = data[i+5];
        i++;
    }
    mese = atoi(temp);
    
    init_str(temp); i=0;
    
    while(i<2){
        
        temp[i] = data[i+8];
        i++;
    }
    giorno = atoi(temp);
    
    return anno*365 + mese*30 + giorno;
}

int time_to_sec(char data[9]){ // converte un orario in secondi per poter poi eseguire confronti (a partire dal secondo 0, ovvero 00:00:00)
    
    int hms[3]; //hour: hms[0], minute: hms[1], second: hms[2]
    int i=0, j;
    char temp[3];
   
    for(j=0; j<3; j++){
        while(i<2){
        
            temp[i] = data[i+3*j]; // i+3*j: per ogni j, l'indice i parte dalla poszione 0 per le ore, poszione 3*(j=1) per i minuti, poszione 3*(j=2) per i secondi
            i++;
        }
        i=0;
        hms[j] = atoi(temp);
    }
    
    return hms[0]*3600 + hms[1]*60 + hms[2];
}

char* key(tratta corse[MAX_R], int ord, int i){
    
    tratta *p_struct;
    p_struct = corse;
    
    if (ord == 3)
        return &(p_struct+i)->codice[0];
    if (ord == 4)
        return &(p_struct+i)->partenza[0];
    if (ord == 5)
        return &(p_struct+i)->destinazione[0];
    
    return 0;
}

