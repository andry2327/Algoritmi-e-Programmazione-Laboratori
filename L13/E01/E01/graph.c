//
//  graph.c
//  E01
//
//  Created by Andrea Pellegrino on 15/01/21.
//

#include "graph.h"
#include <assert.h>

struct graph{
    
    int V;
    int E;
    link z;
    link *list_adj;
    ST st;
    
};

graph_p graph_INIT(int V){
    
    int i;
    graph_p G = malloc(sizeof *G);
    
    G->E = 0;
    G->V = V;
    G->z = NULL;
    G->list_adj = malloc(G->V* sizeof(link));
    for(i=0; i<V; i++)
        G->list_adj[i] = node_INIT();
    G->st = STinit(V);
   
    return G;
}

int graph_add_E(graph_p G, int add){ //se add=0: la funzione ritorna il numero di archi, se add=1: la funzione aggiorna il numero di archi
    
    G->E += add;
    
    return G->E;
}

ST w_graph_ST(graph_p G){
    
    return G->st;
}

void w_ST_insert(graph_p G, char* s){ // w = wrapper
    
    STinsert(G->st, s);
}

int w_ST_search_by_name(char* s, graph_p G){
    
    return ST_search_by_name(s, G->st);
}

link w_ladj_head(graph_p G, int i){
    
    return G->list_adj[i];
}

void new_node(link h, node node){
        
    link x = node_INIT();
    
    if(x==NULL)
        return;
    
    x->w = node.w;
    x->type = node.type;
    x->wt = node.wt;
    x->next = h->next;
    h->next = x;
}



void dfsR(graph_p G, Edge e, int *time, int *pre, int *post, int *st){  //Graph: graph_p, v=vertice=e.v, G->ladj[i]=
    
    link t = malloc(sizeof(*t));
    int v, w = e.w;
    //Edge x;
    
    if (e.v != e.w)
        t->type = 'T';
    st[e.w] = e.v;
    pre[w] = (*time)++;
    
    for(t = G->list_adj[w]->next; t != NULL; t=t->next){ // ERRORE !!!
        if (pre[t->w] == -1)
            dfsR(G, EDGEcreate(w, t->w, e.wt, e.type), time, pre, post, st);
        else{
            v = t->w; // w->v
        
            if (post[v] == -1){
                for(t = G->list_adj[w]->next; t != NULL; t = t->next)
                    if(t->w == v)
                        t->type = 'B';
            }
            else if(pre[v] > pre[w]){
                for(t = G->list_adj[w]->next; t != NULL; t = t->next)
                    if(t->w == v)
                        t->type = 'F';
            }
            else{
                for(t = G->list_adj[w]->next; t != NULL; t = t->next)
                    if(t->w == v)
                        t->type = 'C';
            }
         }
        //assert(t != NULL);
        //t=t->next;
    }
        post[w] = (*time)++;
    }
    


void GRAPHdfs(graph_p G, int id){
    
    int v, time=0, *pre, *post, *st;
    
    pre = malloc(G->V * sizeof(int));
    post = malloc(G->V * sizeof(int));
    st = malloc(G->V * sizeof(int));
    
    for(v=0; v<G->V; v++){
        
        pre[v]=-1; post[v]=-1; st[v]=-1;
    }
    
    dfsR(G, EDGEcreate(id, id, 0, '\0'), &time, pre, post, st);
    
    for(v=0; v < G->V; v++)
        if (pre[v]==-1)
            dfsR(G, EDGEcreate(v, v, 0, '\0'), &time, pre, post, st);
}
 
int is_DAG(graph_p G){
    
    int i=0;
    link t;
    
    for(i=0; i<G->V;i++){
        for(t = G->list_adj[i]->next; t != NULL; t=t->next){
            if(t->w!=-1 && t->type == 'B')
                return 1;
        }
    }
    return 0;
}

int peso_insieme(graph_p G){
    
    int p=0, i;
    link t;
    
    for(i=0; i<G->V;i++){
        for(t = G->list_adj[i]->next; t != NULL; t=t->next){
            if(t->w == -1)
                p += t->wt;
        }
    }
    return p;
}

graph_p C_archi(graph_p G, int k, int peso_max){ // la funzione è stata sviluppata per poter risolvere sia il punto 1. che 2. 
    
    int i, v;
    link t;
    
    if(is_DAG(G) && (peso_insieme(G)>peso_max)){
        
        peso_max = peso_insieme(G);
        return G;
    }
    
    for(i=0; i<k; i++){
        for(i=0; i<G->V;i++){
            for(t = G->list_adj[i]->next; t != NULL; t=t->next){
                if(t->type == 'B'){
                    
                    v = t->w ;
                    t->w = -1;
                    G = C_archi(G, k, peso_max);
                    t->w = v;
                }
                    
            }
        }
    }
    return G;
}

int in_degree(graph_p G, int v){
    
    int i;
    link t;
    int in_deg=0;
    
    for(i=0; i<G->V;i++){
        for(t = G->list_adj[i]->next; t != NULL; t=t->next){
            if(t->w == v){
                
                in_deg++;
            }
        }
    }
    
    return in_deg;
}


void GRAPHspD(graph_p G, int id){

    int v;
    link t;
    PQ pq = PQinit(G->V);
    int *st, *d;
    st = malloc(G->V*sizeof(int));
    d = malloc(G->V*sizeof(int));
    for (v = 0; v < G->V; v++){
        
        st[v] = -1;
        d[v] = maxWT;
        PQinsert(pq, d, v);
    }

    d[id] = 0;
    st[id] = id;
    PQchange(pq, d, id);
    
   while(!PQempty(pq)){
       
       if (d[v = PQextractMin(pq, d)] != maxWT)
         for (t=G->ladj[v]; t!=G->z ; t=t->next)
            if (d[v]< d[t->v] + t->wt){ // relaxation invertita
                d[v] = d[t->v] + t->wt;
                PQchange(pq, d, t->v);
                st[v] = t->v;
            }
   }
    
    printf("\n distanza massima da %s\n", ST_search_by_index(v, G->st));
    
    for (v = 0; v < G->V; v++)
        printf("%s: %d\n", ST_search_by_index(t->v, G->st), d[t->v]);
    Pqfree(pq);
   }
    
