//
//  main.c
//  E01
//
//  Created by Andrea Pellegrino on 09/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_C 255

typedef struct {
    
    char** canzoni; //->canzoni[][]
    int n_canzoni;
}Livello;

int p_molt(int pos, Livello *songs, char** sol, int n, int cnt);

int main(int argc, const char * argv[]) { // principio di moltiplicazione
    
    FILE *fp;
    int n_amici;
    Livello* songs; //->songs[]
    int i, j;
    char** sol; //->sol[][]
    
    fp = fopen("brani.txt","r");
    
    if(fp==NULL){
        printf("errore apertura file\n");
        exit(EXIT_SUCCESS);
    }
    
    fscanf(fp, "%d", &n_amici);
    
    songs = malloc(n_amici*sizeof(Livello));
    
    for (i=0; i<n_amici; i++){
        fscanf(fp, "%d", &songs[i].n_canzoni); printf("%d\n", songs[i].n_canzoni);
        songs[i].canzoni = malloc((songs[i].n_canzoni)*sizeof(char*)); //->n_canzoni * sizeof(str*), puntatore a stringhe
        for (j=0; j<songs[i].n_canzoni; j++){
            songs[i].canzoni[j] = malloc(sizeof(char)*(MAX_C+1));
            fscanf(fp, "%s", songs[i].canzoni[j]);
            printf("%s\n", songs[i].canzoni[j]);
        }
        printf("\n");
    }
    
    sol = malloc(songs[i].n_canzoni*(sizeof(char*)));
    
    for (j=0; j<songs[i].n_canzoni; j++){
        sol[j] = malloc(sizeof(char)*(MAX_C+1));
    }
    
    printf("(soluzioni totali trovate: %d soluzioni)", p_molt(0, songs, sol, n_amici, 0));
    printf("\n\n");
    
    fclose(fp);
}

int p_molt(int pos, Livello *songs, char** sol, int n, int cnt){
    
    int i;
    
    if(pos >= n){ // soluzione trovata, condizione terminale
        printf("---Playlist %d:\n", cnt+1);
        printf("\n");
        for(i=0; i<n; i++)
            printf("  %s\n", sol[i]);
        printf("\n\n");
        return cnt+1;
    }
    
    for(i=0; i<songs[pos].n_canzoni; i++){
        
        strcpy(sol[pos], songs[pos].canzoni[i]);
        cnt = p_molt(pos+1, songs, sol, n, cnt);
    }
    
    return cnt;
}
