//
//  main.c
//  ES2
//
//  Created by Andrea Pellegrino on 13/10/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ROW 1000
#define MAX_DIM 30*8

enum comando_e{r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine};
void selezionaDati(char tabella[][7][MAX_DIM+1], int dim, enum comando_e comando);
int data_to_num(char data[11]);
void f_date(char tabella[][7][MAX_DIM+1], int dim, char data1[11], char data2[11]);
void f_partenza(char tabella[][7][MAX_DIM+1],int dim, char partenza[30+1]);
void f_capolinea(char tabella[][7][MAX_DIM+1],int dim, char capolinea[30+1]);
void f_ritardo(char tabella[][7][MAX_DIM+1], int dim, char data1[11], char data2[11]);
void f_ritardo_tot(char tabella[][7][MAX_DIM+1],int dim, char codice_tratta[30+1]);

void init_str(char s[31]);

enum comando_e leggicomando(char command[]);

int main(int argc, const char * argv[]) {
    
    FILE* fp;
    int num_righe;
    char testo[MAX_ROW][7][MAX_DIM+1]; // creo una matrice tridimensionale per slavare il testo (sarebbe stato più intuitivo usare una struct, ma ho preferito evitarla, dato che avrei dovuto passarla alle funzioni
    char comando[30+1];                                                                        //by reference)
    int i, a;
    
    fp = fopen("log.txt", "r");
    
    if (fp == NULL){
        printf("errore aperura file 'log.txt'\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp, "%d\n", &num_righe);
    
    for(i=0; i<num_righe; i++)
        fscanf(fp, "%s %s %s %s %s %s %s", testo[i][0], testo[i][1], testo[i][2], testo[i][3], testo[i][4], testo[i][5], testo[i][6]); //per semplicità non ho creato un secondo for per leggere testo[i][j], ho
                                                                                                                                       //scritto direttamente l'indice a cui salvare
    fclose(fp);
    
    while(1){
        
        init_str(comando);
   
        printf("Inserisci il tuo comando: (date/partenza/capolinea/ritardo/ritardo_tot ('fine' per terminare)\n");
        scanf("%s", comando);
   
        a = leggicomando(comando);
        selezionaDati(testo, num_righe, a);
    }
    
   
    
    return 0;
}

enum comando_e leggicomando(char command[]){
    
    if(strcmp(command, "date") == 0)
        return r_date;
    else if(strcmp(command, "partenza") == 0)
        return r_partenza;
    else if(strcmp(command, "capolinea") == 0)
        return r_capolinea;
    else if(strcmp(command, "ritardo") == 0)
        return r_ritardo;
    else if(strcmp(command, "ritardo_tot") == 0)
        return r_ritardo_tot;
    else if(strcmp(command, "fine") == 0)
        return r_fine;
    else
        return 0;
 
}

void selezionaDati(char tabella[][7][MAX_DIM+1], int dim, enum comando_e comando){
    
    char date1[11], date2[11];
    char partenza[30+1];
    
    switch(comando){
            
        case r_date:
            scanf("%s%s", date1, date2);
            f_date(tabella, dim, date1, date2);
            break;
            
        case r_partenza:
            scanf("%s", partenza);
            f_partenza(tabella, dim, partenza);
            init_str(partenza);
            break;
            
        case r_capolinea:
            scanf("%s", partenza); //si chiama partenza la variabile, in questo caso è un capolinea (per evitare di creare un nuovo vettore con caratteristiche simili)
            f_capolinea(tabella, dim, partenza);
            init_str(partenza);
            break;
            
        case r_ritardo:
            scanf("%s%s", date1, date2);
            f_ritardo(tabella, dim, date1, date2);
            break;
            
        case r_ritardo_tot:
            scanf("%s", partenza);
            f_ritardo_tot(tabella, dim, partenza); //si chiama partenza la variabile, in questo caso è il codice tratta (per evitare di creare un nuovo vettore con caratteristiche simili)
            init_str(partenza);
            break;
            
        case r_fine:
            exit(EXIT_SUCCESS);
            break;
            
        default:
            printf("comando non riconosciuto\n");
            break;
    }
}

int data_to_num(char data[11]){ // questa funzione converte la data in un numero pari a anno*3 + mese*2 + giorno, per poter operare confronti (< o >) tra date in seguito
    
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
    
    return anno*3 + mese*2 + giorno;
}

void f_date(char tabella[][7][MAX_DIM+1], int dim, char data1[11], char data2[11]){
    
    int i;
    
    printf("le corse partite tra %s e %s sono:\n\n", data1, data2);
    
    for(i=0; i<dim; i++){
        if( (data_to_num(data1) < data_to_num(tabella[i][3])) && (data_to_num(data2) > data_to_num(tabella[i][3])) ){
            printf("%s %s %s %s %s %s %s\n", tabella[i][0], tabella[i][1], tabella[i][2], tabella[i][3], tabella[i][4], tabella[i][5], tabella[i][6]);
        }
    }
    printf("\n");
}

void f_partenza(char tabella[][7][MAX_DIM+1],int dim, char partenza[30+1]){
    
    int i;
    
    printf("le corse partite da %s sono:\n\n", partenza);
    
    for(i=0; i<dim; i++){
        if(strcmp(partenza, tabella[i][1]) == 0 ){
            printf("%s %s %s %s %s %s %s\n", tabella[i][0], tabella[i][1], tabella[i][2], tabella[i][3], tabella[i][4], tabella[i][5], tabella[i][6]);
        }
    }
    printf("\n");
}

void f_capolinea(char tabella[][7][MAX_DIM+1],int dim, char capolinea[30+1]){
    
    int i;
    
    printf("le corse con capolinea a %s sono:\n\n", capolinea);
    
    for(i=0; i<dim; i++){
        if(strcmp(capolinea, tabella[i][2]) == 0 ){
            printf("%s %s %s %s %s %s %s\n", tabella[i][0], tabella[i][1], tabella[i][2], tabella[i][3], tabella[i][4], tabella[i][5], tabella[i][6]);
        }
    }
    printf("\n");
}

void f_ritardo(char tabella[][7][MAX_DIM+1], int dim, char data1[11], char data2[11]){
    
    int i;
    
    printf("le corse partite tra %s e %s in ritardo sono:\n\n", data1, data2);
    
    for(i=0; i<dim; i++){
        if( ((data_to_num(data1) < data_to_num(tabella[i][3])) && (data_to_num(data2) > data_to_num(tabella[i][3]))) && atoi(tabella[i][6]) != 0){
            printf("%s %s %s %s %s %s %s\n", tabella[i][0], tabella[i][1], tabella[i][2], tabella[i][3], tabella[i][4], tabella[i][5], tabella[i][6]);
        }
    }
    printf("\n");
}

void f_ritardo_tot(char tabella[][7][MAX_DIM+1],int dim, char codice_tratta[30+1]){
    
    int i;
    int tot=0;

    printf("il ritardo complessivo accoumulato dalle tratte di codice %s e': ", codice_tratta);
    
    for(i=0; i<dim; i++){
        if(strcmp(codice_tratta, tabella[i][0]) == 0 ){
            tot = tot + atoi(tabella[i][6]);
        }
    }
    
    printf("%d minuti\n", tot);
    printf("\n");
}

void init_str(char s[31]){
    
    int i;
    
    for(i=0; i<strlen(s); i++)
        s[i] = '\0';
}

