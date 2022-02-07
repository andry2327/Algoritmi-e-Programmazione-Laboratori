//
//  main.c
//  ES2
//
//  Created by Andrea Pellegrino on 06/10/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 200
#define MAX_DIZ_LEN 30



int sost(char S[], int start_from, char ricodificata[], char originale[], int n, FILE* fp_recode);

int main(int argc, const char * argv[]) {
    
    FILE* fp_text;
    FILE* fp_diz;
    FILE* fp_recode;
    char S[MAX_LEN+1];
    char recode[MAX_DIZ_LEN][MAX_LEN+1];
    char original[MAX_DIZ_LEN][MAX_LEN+1];
    int diz_righe;
    int i=0;
    int index=0;
    int new_index=0;
    int flag=0;

    fp_text = fopen("sorgente.txt", "r");
    
    if (fp_text==NULL){
        printf ("errore apertura file 'sorgente.txt'");
        exit(EXIT_FAILURE);
    }
    
    fp_diz = fopen("dizionario.txt", "r");
    
    if (fp_diz==NULL){
        printf ("errore apertura file 'dizionario.txt'");
        exit(EXIT_FAILURE);
    }
    
    fp_recode = fopen("ricodificato.txt", "w");
    
    if (fp_recode==NULL){
        printf ("errore apertura file 'ricodificato.txt'");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp_diz, "%d", &diz_righe);
    
    for(i=0; i<diz_righe; i++){
        
        fscanf(fp_diz, "%s%s", recode[i], original[i]);
    }
    i=0;
        
    while (fgets(S, MAX_LEN, fp_text) != NULL){  //lettura stringhe da sorgente.txt
        while((flag == 0) && (new_index < strlen(S)-strlen(original[i])+1)){
            while(i<diz_righe){
                index = new_index;
                new_index = sost(S, index, recode[i], original[i], diz_righe, fp_recode);
                i++;
            }
        
            if(new_index == index){ // ovvero se per ogni parola del dizionario non è stata trovata una parola nel testo corrispondente all' indice index
                fputc(S[new_index], fp_recode);
                new_index++;
                i=0;
            }else
                flag=1;
        }
        new_index=0;
        i=0;
       
    }
    
    printf("il file ricodificato e' stato salvato con successo!");
    printf("\n\n");
    
    fclose(fp_text);
    fclose(fp_recode);
    fclose(fp_recode);
        
    
    return 0;
}

int sost(char S[], int start_from, char ricodificata[], char originale[], int n, FILE* fp_recode){
    
    int j=0;
    int k=0;
    int found = 0;
    
        while((k<strlen(originale)) && (found == 0)){
            if(S[start_from+k] == originale[k]){
                k++;
                if (k == strlen(originale))
                    found = 1;
            }else
                found = -1;
        }
    if (found == 1){
            for(j=start_from; j<start_from-1; j++)
                fprintf(fp_recode, "%c", S[j]);
            
            fprintf(fp_recode, "%s", ricodificata);
            start_from = start_from + (int)strlen(originale);
        }
    return start_from;
}
