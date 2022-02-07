//
//  main.c
//  E03
//
//  Created by Andrea Pellegrino on 03/11/2020.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_C 50

char *cercaRegexp (char* src, char *regexp);

int re_char (char* src, char *regexp, int *j);
int re_multichar (char* src, char *regexp, int *j);
int re_notchar (char* src, char *regexp, int *j);
int re_lowerchar (char* src, int *j);
int re_upperchar (char* src, int *j);

int main(int argc, const char * argv[]) {
    
    char src[MAX_C+1]; // defisico una lunghezza massima della stringa in cui cercare uan regesxp
    char regexp[MAX_C+1];
    char* s = NULL;
    int i=0;
    
    printf("inserisci stringa (max 50 caratteri):\n");
    fgets(src, MAX_C, stdin);  //uso fgets( , , stdin) invece che gets per eviare il warning "this program uses gets(), which is unsafe."
    src[strlen(src)-1] = '\0';  // sostituisco il carattere "\n" in poszione terminale della stringa,  preso dall' input, con '\0'
    
    printf("\n");
    
    printf("inserisci un'espressione regolare (max 50 caratteri):\n");
    fgets(regexp, MAX_C, stdin);
    regexp[strlen(regexp)-1] = '\0';
    
    printf("\n");
    
    s = cercaRegexp(src, regexp);
    
    if(s==NULL)
        printf("Nessuna occorrenza trovata\n\n");
    else{
        printf("Occorrenza trovata: ");
        while(isalpha(s[i])){
            printf("%c", s[i]);
            i++;
        }
        printf("\n\n");
    }
        
    
    return 0;
}

char *cercaRegexp (char* src, char *regexp){
    
  
    int i=0, j=0, k=0;
    int found=0;
    
    while (i < strlen(src)){
        do{
            found=0;
            if(isalpha(regexp[j])){
                if (regexp[j] == src[i+k]){
                    
                    found=1;
                }
                
            }else{
                if(regexp[j] == '.'){
                    
                    found = re_char(src+(i+k), regexp+(1+j), &j);
    
                    
                }else if(regexp[j] == '\\'){
                    if(regexp[j+1] == 'a'){
                        
                        found = re_lowerchar(src+(i+k),&j);
                    }else if(regexp[j+1] == 'A'){
                        
                        found = re_upperchar(src+(i+k), &j);
                    }
                }
                else if(regexp[j] == '|'){  //utilizzo le tonde al posto delle graffe, il mio computer non riesce ad interpretare ']' nel modo corretto
                    if(regexp[j+1] == '^'){
                        
                        found = re_notchar(src+(i+k), regexp+2+j, &j);
                        
                    }else{
                        
                        found = re_multichar(src+(i+k), regexp+1+j, &j);
                    }
                }
            }
            
            if(found){
                j++;
                k++;
            }
            else{
                j=0;
                k=0;
            }
            
        }while((j < strlen(regexp)) && (found!=0));
        
        if(j>=strlen(regexp))
            return src+i;
        
        i++;
    }
    
    return NULL;
}


int re_char (char* src, char *regexp, int *j){
    
    int l=0;
    
    while(l < strlen(regexp) && isalpha(regexp[l])) //conta il numero di lettere dopo '.' della regexp
        l++;
    
    if ( (strncmp(regexp, src+1, l)==0) ){  //faccio anche il controllo che la regexp sia temrinale in src
        
        *j += l+1;
        return 1;
    }
    
    return 0;
}

int re_multichar (char* src, char *regexp, int *j){
    
    int m=0; int flag=0; 
    
    while(isalpha(regexp[m])){
        if(src[0] == regexp[m]){
            flag=1;
        }
        m++;
    }
    
    if(flag){
        *j += m+1;
        return 1;
    }

    return 0;
}

int re_notchar (char* src, char *regexp, int *j){
    
    int m=0; int flag=1;
    
    while(isalpha(regexp[m])){
        if(src[0] == regexp[m])
            flag=0;
        m++;
    }
    
    if(flag){
        *j += m+2;
        return 1;
    }
    
    return 0;
}

int re_lowerchar (char* src, int *j){
    
    if(islower(src[0])){
        *j += 1;
        return 1;
    }
 
    return 0;
}

int re_upperchar (char* src, int *j){
    
    if(isupper(src[0])){
        *j += 1;
        return 1;
    }
    return 0;
}
