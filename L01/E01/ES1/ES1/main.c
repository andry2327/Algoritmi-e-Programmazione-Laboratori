//
//  main.c
//  ES1
//
//  Created by Andrea Pellegrino on 05/10/2020.
//

#include <stdio.h>

int cerca_max(int vett[], int n);

int main(int argc, const char * argv[]) {
    
    FILE* fp;
    int m, n;
    int i, j;
    int num;
    int winner = 0;

    
    fp = fopen("mat.txt", "r");
    
    if (fp==NULL)
        printf("errore apertura file");
    
    fscanf(fp, "%d%d", &n, &m); //n = mie colonne (squadra), m = mie righe (giornata)
    
    int mat[m][n];
    int g[n];
    
    for(i=0; i<n; i++)  // inizializzo ogni entrata del vettore a 0
    g[i] = 0;
    
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            
            fscanf(fp, "%d", &num);
            mat[j][i] = num; //ho invertito la matrice
        }
    }
    
    //mi serve stampare l'indice della colonna corrispondente alla squadra
    
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            
            g[j] = mat[i][j] + g[j];
        }
        winner = cerca_max(g, n);
        printf("La capolista alla giornata %d e' la squadra %d\n", i+1, winner+1);
    }

    printf("\n");
    printf("Il vincitore del campionato e' la squadra %d\n", winner+1); //non richiesto
    printf("\n");
    
    return 0;
}

int cerca_max(int vett[], int n){
    
    int j=0;
    int max = 0;
    int team=0;
    
    for(j=0; j<n; j++){
        if(vett[j] > max){
            
            max = vett[j];
            team = j;
        }
    }
    
    return team;
}


