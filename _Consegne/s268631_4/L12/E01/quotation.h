//
//  quotation.h
//  E01
//
//  Created by Andrea Pellegrino on 11/01/21.
//

#ifndef quotation_h
#define quotation_h

#include <stdio.h>
#include "date_time.h"

typedef struct BST_node *q_BST_link;
typedef struct quotation_BST *BST;

typedef struct quotation{
    
    date q_date;
    double value;
    
}quotation;

int is_different_date(date tmp, date curr_tmp);
double BST_search_by_date(BST bst, q_BST_link next, date date);
double BST_search_by_date_interval(BST bst, q_BST_link next, date date1, date date2, int M, double *q_M);
BST BSTinit(void);
void BST_print_wrapper(BST bst);
double print_in_data_wrapper(BST bst, date date);
double BST_search_by_date_interval_wrapper(BST bst, date date1, date date2, int M);
int BST_lenght_wrapper(BST bst, int M);
q_BST_link rotR(q_BST_link h);
q_BST_link rotL(q_BST_link h);
q_BST_link partR(q_BST_link h, int r);
void BSTbalance(BST bst, int S);
int BST_lenght(q_BST_link next, int M);
void BST_print(BST bst, q_BST_link next);
quotation Qinit(void);
double calc_quotatation(int value, int n_title, int* curr_tmp_n_title, double curr_q);
int key_cmp(date k1, date k2);
void BSTinsert_leafR(BST bst, quotation x);
void BSTfree(BST bst);
int max(int a, int b);
int min(int a, int b);

#endif /* quotation_h */
