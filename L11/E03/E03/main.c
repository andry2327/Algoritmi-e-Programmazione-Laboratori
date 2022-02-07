//
//  main.c
//  E03
//
//  Created by Andrea Pellegrino on 23/12/20.
//

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, const char * argv[]) {
    
    FILE* fp;
    graph_t G;
    int cmd;
    char v1[30], v2[30], v3[30];
    
    fp = fopen(argv[1], "r");
    
    if(fp==NULL){
        
        printf("errore apertura file");
        exit(EXIT_FAILURE);
    }
    
    G = graphLOAD(fp);
    
    while(1){
        
        printf("1: elenco ordine alfabetico\n2: verificare adiacenza a coppie\n3: genera lista di adiacenza\n4: exit"); printf("\n\n");
        printf("comando: ");
        scanf("%d", &cmd);
        
        switch(cmd){
                
            case 1:
                
                graph_print_ord(G);
                break;
                
            case 2:
                
                printf("inserisci il nome dei 3 vertici: ");
                scanf("%s %s %s", v1, v2, v3);
                
                if(is_ad_coppie(G, v1, v2, v3)){
                    printf("\nI 3 veritici sono adicenti a coppie, il sottografo dei 3 vertici è completo\n\n");
                }else
                    printf("\nI 3 veritici non sono adicenti a coppie, il sottografo dei 3 vertici non è completo\n\n");
                break;
            
            case 3:
                
                graph_list_adjINIT(G);
                graph_list_adjCREATE(G);
                
                printf("\nlista di adiacenza creata\n\n");
                
                break;
                
            case 4:
                
                free_graph(G);
                exit(EXIT_SUCCESS);
                
            default:
                printf("comando errato"); printf("\n\n");    //     Shiva Ifrit Alderaan
        }
    }

    return 0;
}
