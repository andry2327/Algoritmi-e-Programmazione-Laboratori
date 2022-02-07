//
//  graph.h
//  E03
//
//  Created by Andrea Pellegrino on 23/12/20.
//

#ifndef graph_h
#define graph_h

#include <stdio.h>

typedef struct graph* graph_t;
typedef struct node* link;

graph_t graphINIT(void);
graph_t graph_madjINIT(graph_t G);
graph_t graphLOAD(FILE* fp);

void graph_list_adjINIT(graph_t G);
void graph_list_adjCREATE(graph_t G);

void graph_print_ord(graph_t G);
int is_ad_coppie(graph_t G, char* v1, char* v2, char* v3);
void free_graph(graph_t G);

#endif /* graph_h */
