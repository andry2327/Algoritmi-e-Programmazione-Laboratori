//
//  graph.c
//  E03
//
//  Created by Andrea Pellegrino on 23/12/20.
//

#include <stdlib.h>
#include "graph.h"
#include "ST.h"

struct graph{
    
    int V;
    int E;
    int **madj;
    link *head; // vettore di puntatori a struct nodo
    int flag_list; //mi dice se è stata inizializzata la lista delle adiacenze
    ST tab;
};

struct node{
    
    int v;
    int wt;
    link next;
};

link create_node(link h, int k, int wt){
    
    link x = malloc(sizeof(*x));
    if(x==NULL)
        return NULL;
    
    x->v = k;
    x->wt = wt;
    
    x->next = h;
    h = x;
    
    return h;
}

graph_t graphINIT(void){

    graph_t G = malloc(sizeof *G);
    
    G->tab = STinit(1);
    
    G->E=0;
    G->V=0;
    
    return G;
}

graph_t graph_madjINIT(graph_t G){

    int i, j;
    int dim = G->V;
    
    G->madj = malloc(dim*sizeof(*G->madj));
    for(i=0; i<dim; i++){
        G->madj[i] = malloc(dim*sizeof(**G->madj));
        for(j=0; j<dim; j++)
            G->madj[i][j] = 0;
    }
    
    G->flag_list=0;
    
    return G;
}

graph_t graphLOAD(FILE* fp){
    
    char e1[30], r1[30], e2[30], r2[30];
    int wt;
    int i, j;
    graph_t G;
    int index;
    
    G = graphINIT();
    
    while(fscanf(fp, "%s%s%s%s%d", e1, r1, e2, r2, &wt)!=EOF){ // lettura 1 del file per slavare i nodi in G->tab
        
        index = STsearch_by_name(e1, G->tab);
        if(index==-1){
            STinsert(G->tab, r_elab_create(e1, r1));
        }
        
        index = STsearch_by_name(e2, G->tab);
        if(index==-1){
            STinsert(G->tab, r_elab_create(e2, r2));
        }
    }

    G->V = STget_size(G->tab);
    G->tab = ST_ord_by_name(G->tab, G->V);  // ordino la ST durante l'inizialiizzazione del grafo per comodità 
    G = graph_madjINIT(G);
    
    rewind(fp);
    
    while(fscanf(fp, "%s%s%s%s%d", e1, r1, e2, r2, &wt)!=EOF){ // lettura 2 del file per slavare gli archi in **madj
        
        i = STsearch_by_name(e1, G->tab);
        j = STsearch_by_name(e2, G->tab);
        
        G->madj[i][j] = G->madj[j][i] = wt; // archi non orientati
    }
    
    fclose(fp);
    
    return G;
}


/*funzioni per lista adiacenze*/


void graph_list_adjINIT(graph_t G){
    
    int i;
    
    G->head = malloc((G->V)*sizeof(*G->head));
    G->flag_list = 1;
    for(i=0; i<G->V; i++){
        G->head[i] = malloc(sizeof(*G->head[i]));
        G->head[i]->next = NULL;
    }
    
    return;
}

void graph_list_adjCREATE(graph_t G){
    
    int i, j;
    
    for(i=0; i<G->V; i++){
        for(j=0; j<G->V; j++){
            if(G->madj[i][j] != 0){
                
                G->head[i]->next = create_node(G->head[i]->next, j, G->madj[i][j]); // inserzione in testa del nuovo nodo
            }
        }
        
    }
    
}

/*
 
 
 */

void graph_print_ord(graph_t G){
    
    int i, j;
    
    printf("\n");
    
    for(i=0; i<G->V; i++){
        
        printf("Vertice %d: %s %s, con vertici adiacenti:\n\n", i, STsearch_by_index(i, G->tab), STsearch_by_index_rete(i, G->tab));
        
        for(j=0; j<G->V; j++){
            
            if(G->madj[i][j] != 0){
                printf("%s %s, peso arco: %d\n", STsearch_by_index(j, G->tab), STsearch_by_index_rete(j, G->tab), G->madj[i][j]);
            }
        }
        printf("\n-------------\n\n");
    }
}

static int is_ad_coppie_MADJ(graph_t G, int n1, int n2, int n3){
    
    /* controllo su riga di n1*/
    if( (G->madj[n1][n2]==0) || (G->madj[n1][n3]==0) )
        return 0;
    
    /* controllo su riga di n2*/
    if( (G->madj[n2][n1]==0) || (G->madj[n2][n3]==0) )
        return 0;
    
    /* controllo su riga di n3*/
    if( (G->madj[n3][n1]==0) || (G->madj[n3][n1]==0) )
        return 0;
    
    return 1;
}

static int is_ad_coppie_LIST(graph_t G, int n1, int n2, int n3){
    
    link x;
    int t1=0, t2=0;
    /* controllo su lista di n1*/
    for(x=G->head[n1]->next; x!=NULL; x=x->next){
        
        if(x->v == n2) t1=1;
        if(x->v == n3) t2=1;
    }
    
    if(t1 && t2){  t1=t2=0;
        /* controllo su lista di n2*/
        for(x=G->head[n2]->next; x!=NULL; x=x->next){
            
            if(x->v == n1) t1=1;
            if(x->v == n3) t2=1;
        }
        
        if(t1 && t2){  t1=t2=0;
            /* controllo su lista di n3*/
            for(x=G->head[n3]->next; x!=NULL; x=x->next){
                
                if(x->v == n1) t1=1;
                if(x->v == n2) t2=1;
            }
            
            if(t1 && t2)
                return 1;
            return 0;
        }
        return 0;
    }
    return 0;
}

int is_ad_coppie(graph_t G, char* v1, char* v2, char* v3){
    
    int flag_madj=0, flag_list=0;
    int n1 = STsearch_by_name(v1, G->tab);
    int n2 = STsearch_by_name(v2, G->tab);
    int n3 = STsearch_by_name(v3, G->tab);
    
    flag_madj = is_ad_coppie_MADJ(G, n1, n2, n3);
    if(G->flag_list) flag_list = is_ad_coppie_LIST(G, n1, n2, n3);  // esegue la funzione solo se esiste la lista di adiacenze
    
    if(flag_madj) // faccio il controllo solo per la funzione con la madj: entrambe le funzioni ritornano lo stesso risultato -> faccio il controllo su una sola
        return 1;
    return 0;
}

void free_adjLISt(link h){
    
    if(h->next==NULL){
        free(h);
        return;
    }
    
    free_adjLISt(h->next);
}

void free_graph(graph_t G){
    
    int i;
    
    STfree(G->tab);
    
    for(i=0; i<G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    
    if(G->flag_list){
        for(i=0; i<G->V; i++)
            free_adjLISt(G->head[i]);
        free(G->head);
    }
}

/*
for(i=0; i<G->V; i++){
    for(j=0; j<G->V; j++){
        
        printf("%d      ", G->madj[i][j]);
    }
    printf("\n");
}
printf("\n");

for(j=0; j<G->V; j++){
    
    printf("%s %d\n", STsearch_by_index(j, G->tab), j);
}*/
