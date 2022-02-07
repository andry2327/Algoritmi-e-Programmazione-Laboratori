//
//  stock.c
//  E01
//
//  Created by Andrea Pellegrino on 11/01/21.
//

#include <stdlib.h>
#include <string.h>
#include "stock.h"


#define MAX_L 20

struct stock{
    
    char name[MAX_L];
    int n_transaction;
    stock_link next;
    BST bst;
};

struct stock_collection{
    
    int n_stock;
    stock_link head;
};

stock_link INIT_stock(void){
    
    stock_link s;
    
    s = malloc(sizeof *s);
    s->bst = BSTinit();
    s->n_transaction = 0;
    s->next = NULL;
    
    return s;
}

void PRINT_stock(stock_link s_link){
    
    printf("\n");
    printf("%s:\n\n", s_link->name);
    printf("N transazioni: %d\n", s_link->n_transaction);
    BST_print_wrapper(s_link->bst);
    printf("\n");
}

double PRINT_stock_in_data(stock_link s_link, date date){
    
    double d;
    
    printf("\n");
    printf("%s:\n", s_link->name);
    d = print_in_data_wrapper(s_link->bst, date);
    printf("\n");
    
    return d;
}

double PRINT_q_in_intervallo(stock_link s_link, date date1, date date2, int M){

    return BST_search_by_date_interval_wrapper(s_link->bst, date1, date2, M);
}

stock_list INIT_list(void){
    
    stock_list s_list;
    s_list = malloc(sizeof *s_list);
    s_list->n_stock = 0;
    s_list->head = INIT_stock();
    s_list->head->next = INIT_stock();
    
    return s_list;
}

void INSERT_n_stock(int n, stock_list s_list){
    
    s_list->n_stock = n;
}

stock_link SEARCH_in_list(stock_link node, stock_list s_list){
    
    stock_link x, p;
    
    for(x=s_list->head->next, p=s_list->head; (x->name[0] != '\0') && strcmp(node->name, x->name)>0; p=x, x=x->next);
        
    if(strcmp(x->name, node->name)==0)
        return x;
        
    return p;
}

stock_link NEW_stock_node(char title[20], stock_list s_list, int n_temp){
    
    stock_link x = malloc(sizeof *x), p;
    
    x->bst = BSTinit();
    x->n_transaction = 0;
    strcpy(x->name, title);
    
    p = SEARCH_in_list(x, s_list);
    
    x->next = p->next;
    p->next = x;
    x->n_transaction = n_temp;
    
    return x;
}

void INSERT_title_stock(stock_link s_link, char* s){
    
    strcpy(s_link->name, s);
}

void BSTinsert_leafR_wrapper(stock_list list, quotation x, stock_link node){
    
    BSTinsert_leafR(node->bst, x);
}

int BST_lenght_wrap2(stock_link s_link, int M){
    
    return BST_lenght_wrapper(s_link->bst, M);
}

void BSTbalance_wrapper(stock_link s_link, int S){
    
    BSTbalance(s_link->bst, S);
}

void free_stock_link(stock_link s){
    
    BSTfree(s->bst);
    free(s->name);
    free(s->next);
}

void free_stock_link_list(stock_link s){
    
    if(s->next==NULL)
        return;
    free_stock_link_list(s->next);
    
    free(s);
}

void free_list(stock_list list){
    
    free_stock_link_list(list->head);
    free(list);
}


