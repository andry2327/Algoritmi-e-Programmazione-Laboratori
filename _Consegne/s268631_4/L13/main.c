//
//  main.c
//  E01
//
//  Created by Andrea Pellegrino on 15/01/21.
//

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

graph_p leggi_graph(void);

int main(int argc, const char * argv[]) {
    
    graph_p G, GG;
    int i, j, k;
    int d_max=0;
    
    G = leggi_graph();
    
    printf("individuazione degli insiemi di archi di cardinalità minima:\n");
    GRAPHdfs(G, 0);
    
    for(k=0; k<graph_add_E(G, 0); k++){ 
        
        GG = C_archi(G, k, 0); // uso una variabile diversa solo per migliore comprensione dell'esercizio
        
        for(i=0; i<graph_add_E(G, 0); i++){
            
            // ordinamento topologico
            
            
            if(in_degree(G, i)==0){ // controllo se il vertice i è un nodo sorgente, cioe se il suo in_degree = 0;
                
                for(j=0; j<graph_add_E(G, 0); j++){
                    
                    GRAPHspD(G, j);
                }
                printf("\n");
            }
        }
    }
    
  
    
    
    
    return 0;
}

graph_p leggi_graph(void){
    
    graph_p G;
    FILE* fp;
    int V;
    int i;
    char str_id[30], e_str_id[30];;
    node node;
    link h_i = node_INIT();
    
    fp=fopen("grafo1.txt", "r");
    
    if(fp==NULL){
        
        printf("errore apertura file\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp, "%d", &V);
    G = graph_INIT(V);
    
    for(i=0; i<V; i++){
        fscanf(fp, "%s", str_id);
        w_ST_insert(G, str_id); // w = wrapper
    }
    
    while(fscanf(fp, "%s %s %d", str_id, e_str_id, &node.wt) != EOF){
        
        node.w = w_ST_search_by_name(e_str_id, G);
        h_i = w_ladj_head(G, w_ST_search_by_name(str_id, G));
        new_node(h_i, node);
        graph_add_E(G, 1);
    }
    
    return G;
}
