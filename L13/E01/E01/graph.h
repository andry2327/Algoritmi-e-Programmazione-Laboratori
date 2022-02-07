//
//  graph.h
//  E01
//
//  Created by Andrea Pellegrino on 15/01/21.
//

#ifndef graph_h
#define graph_h

#include <stdio.h>
#include <stdlib.h>
#include "ST.h"

typedef struct graph* graph_p;

graph_p graph_INIT(int V);
int graph_add_E(graph_p G, int add);
ST w_graph_ST(graph_p G);
void w_ST_insert(graph_p G, char* s);
int w_ST_search_by_name(char* s, graph_p G);
link w_ladj_head(graph_p G, int i);
void new_node(link h, node node);

void dfsR(graph_p G, Edge e, int *time, int *pre, int *post, int *st);
void GRAPHdfs(graph_p G, int id);
int is_DAG(graph_p G);
graph_p C_archi(graph_p G, int k, int peso_max);
int in_degree(graph_p G, int v);

void GRAPHspD(graph_p G, int id);

#endif /* graph_h */
