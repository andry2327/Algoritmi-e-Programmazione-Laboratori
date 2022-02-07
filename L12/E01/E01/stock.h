//
//  stock.h
//  E01
//
//  Created by Andrea Pellegrino on 11/01/21.
//

#ifndef stock_h
#define stock_h

#include <stdio.h>
#include "stock.h"
#include "quotation.h"

typedef struct stock* stock_link;
typedef struct stock_collection* stock_list;

stock_link INIT_stock(void);
void PRINT_stock(stock_link s_link);
double PRINT_stock_in_data(stock_link s_link, date date);
double PRINT_q_in_intervallo(stock_link s_link, date date1, date date2, int M);
stock_list INIT_list(void);
void INSERT_n_stock(int n, stock_list head);
stock_link SEARCH_in_list(stock_link node, stock_list s_list);
stock_link NEW_stock_node(char title[20], stock_list s_list, int n_temp);
void INSERT_title_stock(stock_link s_link, char* s);
void BSTinsert_leafR_wrapper(stock_list list, quotation x, stock_link node);
int BST_lenght_wrap2(stock_link s_link, int M);
void BSTbalance_wrapper(stock_link s_link, int S);
void free_stock_link(stock_link s);
void free_stock_link_list(stock_link s);
void free_list(stock_list list);

#endif /* stock_h */
