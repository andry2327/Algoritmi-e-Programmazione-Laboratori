//
//  main.c
//  ES3
//
//  Created by Andrea Pellegrino on 15/10/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_DIM_N_SEQ 20
#define MAX_DIM_SEQ 5
#define MAX_DIM_WORD 25

typedef struct{
    char word[MAX_DIM_WORD+1];
    int word_pos;
}word_pos;

void init_str(char s[MAX_DIM_WORD+1]);

int cerca_occ(char occ[MAX_DIM_N_SEQ][MAX_DIM_SEQ+1], int dim, char parola[MAX_DIM_WORD+1]);

int main(int argc, const char * argv[]) {
    
    FILE *fp_seq;
    FILE *fp_text;
    int num_seq;
    int i, j=0;
    char char_r = '\0';
    char s[MAX_DIM_WORD+1];
    char seq[MAX_DIM_N_SEQ][MAX_DIM_SEQ+1];
    int occ_len[MAX_DIM_N_SEQ] ; //salvo in questo vettore il numero di parole trovate nel testo contenente l'occorrenza, in corrispondenza della posizione i-esima
    int index=0;
    int i_testo=1;
    
    word_pos parola_found[MAX_DIM_N_SEQ][10]; //identifico solo le prime 10 occorrenze nel testo
    
    fp_seq = fopen("sequenze.txt", "r");
    
    if(fp_seq == NULL){
        
        printf("errore apertura file sequenze.txt");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp_seq, "%d", &num_seq);
    
    for(i=0; i<num_seq; i++)  //salvo il file di sequenze in un vettore di stringhe (matrice di caratteri)
        fscanf(fp_seq, "%s", seq[i]);
    
    fclose(fp_seq);
    
    fp_text = fopen("testo.txt", "r");
    
    if(fp_text == NULL){
        
        printf("errore apertura file testo.txt");
        exit(EXIT_FAILURE);
    }
    
    for(i=0; i<MAX_DIM_N_SEQ; i++)  //inizializzo il vettore occ_len[] a 0
        occ_len[i] = 0;
    
    init_str(s);  // inizializzo la stringa s[] con \0
    
    while(fscanf(fp_text, "%c", &char_r) != EOF){
        
        if ( isalnum(char_r) ){
            s[j] = char_r; //crea la parola letta carattere per carattere, in modo da salavre solo i caratteri alfanumerici
            j++;
        }else{
            if(strlen(s) != 0){  // * solo le stringhe che contengono caratteri alfanumerici (if not vengono stampate righe vuote)
                s[j] = '\0';
                index = cerca_occ(seq, num_seq, s);  //salvo in found l'indice della parola torvata, corrispondente alla stessa sequenza in seq[i][MAX_DIM_SEQ+1]
                if (index != -1){
                    
                    strcpy(parola_found[index][occ_len[index]].word, s); // salvo nella matrice di struct( .word) la parola del testo in cui si trova la seq
                    parola_found[index][occ_len[index]].word_pos = i_testo;
                    //printf("%s %d\n", parola_found[index][occ_len[index]].word, parola_found[index][occ_len[index]].word_pos);
                    occ_len[index] += 1;  //la seq (in pos [found]) e stata trovata +1 volte
                }
                
                i_testo += 1; // la parola successiva sarà in posizione i_testo + 1
            }
            
            init_str(s);
            j=0;
        }
    }
    
    for(i=0; i<num_seq; i++){
        if ( occ_len[i] == 0){
            printf("la sequenza '%s' non e' stata trovata nel testo.", seq[i]);
            printf("\n\n");
        }else{
            printf("la sequenza '%s' e' contenuta in ", seq[i]);
            for(j=0; j<occ_len[i]-1; j++)
                printf("'%s' (posizione %d), ", parola_found[i][j].word, parola_found[i][j].word_pos);
            printf("e '%s' (posizione %d).", parola_found[i][j].word, parola_found[i][j].word_pos);
            printf("\n\n");
        }
    }
    
    fclose(fp_text);
    return 0;
}

void init_str(char s[MAX_DIM_WORD+1]){
    
    int i;
    
    for(i=0; i<MAX_DIM_WORD+1; i++) //(strlen not working)
        s[i] = '\0';
}
                         
int cerca_occ(char occ[MAX_DIM_N_SEQ][MAX_DIM_SEQ+1], int dim, char parola[MAX_DIM_WORD+1]){
    
    int i, j, k;
    int found=0;
    
    for(i=0; i<dim; i++)
        if( strlen(occ[i]) <= strlen(parola) ){  //faccio un controllo solo nel caso in cui la sequenza abbia lunghezza minore della parola
           
            for(j=0; j<strlen(parola)-strlen(occ[i])+1; j++){
                for(k=0;k<strlen(occ[i]); k++){
                    if( tolower(occ[i][k]) == tolower(parola[j+k]) )   //nel caso una delle due lettere sia maiuscola la trasformo in minuscola per il confronto
                        found++;
                }
                if ( found == strlen(occ[i]) ){
                    return i;
                }
                found=0;
            }
        
        
        }
    return -1;
}
                         
                         
                         
                         

                         
        

