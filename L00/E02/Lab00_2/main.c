//
//  main.c
//  Lab00_2
//
//  Created by Andrea Pellegrino on 02/10/2020.
//

#include <stdio.h>
#include <string.h>
#define N 20

int conta (char S[20], int n);
int is_in_2_vocal(char parola[20]);

int main(int argc, const char * argv[]) {
    
    FILE* fp;
    char nomefile[N+1];
    char word[N+1];
    int sstr_len;
    int max_row;
    int n_sstr;
    int n_sstr_tot = 0;
    
    printf("inserisci nome del file:\n");
    scanf("%s", nomefile);

    printf("inserisci la lunghezza delle sottostringhe da ceracre:\n");
    scanf("%d", &sstr_len);
    
    fp = fopen(nomefile, "r");
    
    if(fp == NULL)
        printf("Errore Apertura file.");
    
    fscanf(fp, "%d", &max_row);
    
    printf("numero righe: %d\n\n", max_row);
    
    while(fscanf(fp, "%s", word) != EOF){
        if (strlen(word) >= sstr_len){
            
            n_sstr = conta(word, sstr_len);
            n_sstr_tot = n_sstr_tot + n_sstr;
        }
    }
    
    printf("\nil numero complessivo di sottostringhe e': %d\n\n", n_sstr_tot);
    
    fclose(fp);

    return 0;
}

int conta (char S[20], int n){
    
    int ns=0;
    int i;
    int j;
    char sstr[n+1];
    
    for(i = 0; i < strlen(S)-n+1; i++){
        for(j = 0; j < n; j++){
            
            sstr[j] = S[j+i];
        }
        ns = ns + is_in_2_vocal(sstr);
    }
    
    return ns;
}

int is_in_2_vocal(char parola[20]){
    
    int flag=0;
    int i;
    int vocal_found=0;
    
    for(i=0; i<strlen(parola); i++){
        if((parola[i] == 'a') || (parola[i] == 'e') || (parola[i] == 'i') || (parola[i] == 'o') || (parola[i] == 'u')){  //considero il caso in cui non ci siano                                                                                                                //vocali maiuscole
            vocal_found++;
        }
    }
    
    if (vocal_found >= 2){
        
        flag = 1;
        printf("%s\n", parola);
    }
    
    return flag;
}
