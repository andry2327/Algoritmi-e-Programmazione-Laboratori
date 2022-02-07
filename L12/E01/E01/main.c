//
//  main.c
//  E01
//
//  Created by Andrea Pellegrino on 11/01/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stock.h"

stock_list new_file(char* nome_file, stock_list s_list);

int main(int argc, const char * argv[]) {
    
    char* temp_str = malloc(sizeof(*temp_str));
    int cmd;
    int S;
    double min, max;
    stock_list s_list = INIT_list();
    stock_link s_p = INIT_stock();
    date temp_data, temp_data2; double qu;
    
    
    while(1){
        
        printf("1. Acquisizione da nuovo file\n"
               "2. Ricerca titolo azionario\n"
               "3. Ricerca quotazione in data\n"
               "4. Ricerca quotazione Min e Max, in intervallo date\n"
               "5. Ricerca quotazione quotazione Min e Max totale\n"
               "6. Bilanciamento albero\n\n");
        
        printf("inserisci comando (0 per uscire): ");
        scanf("%d", &cmd);
        
        switch(cmd){
                
            case 1:
                
                temp_str = calloc(1, sizeof *temp_str);
                printf("inserire nome file: ");
                scanf("%s", temp_str);
                s_list = new_file(temp_str, s_list);      //     F1.txt
                printf("\n");
                break;
            
            case 2:
                
                temp_str = calloc(1, sizeof *temp_str);
                printf("inserisci titolo azionario: ");
                scanf("%s", temp_str); INSERT_title_stock(s_p, temp_str);
                s_p = SEARCH_in_list(s_p, s_list);
                PRINT_stock(s_p);
                break;
                
            case 3:
                
                printf("inserisci titolo azionario e data (aaaa/mm/gg): "); temp_str = calloc(1, sizeof *temp_str);
                scanf("%s%d/%d/%d", temp_str, &temp_data.year, &temp_data.month, &temp_data.day); INSERT_title_stock(s_p, temp_str);
                s_p = SEARCH_in_list(s_p, s_list);
                qu = PRINT_stock_in_data(s_p, temp_data);
                
                if(qu==-1)
                    printf("Non è stata trovata alcuna quotazione in questa data\n");
                else
                    printf("%d/%d/%d: %f\n\n", temp_data.year, temp_data.month, temp_data.day, qu);
                
                break;
                
            case 4:
                
                printf("inserisci titolo azionario, data1 e data2 (aaaa/mm/gg): "); temp_str = calloc(1, sizeof *temp_str);
                scanf("%s %d/%d/%d %d/%d/%d", temp_str, &temp_data.year, &temp_data.month, &temp_data.day, &temp_data2.year, &temp_data2.month, &temp_data2.day); INSERT_title_stock(s_p, temp_str);
                s_p = SEARCH_in_list(s_p, s_list);
                min = PRINT_q_in_intervallo(s_p, temp_data, temp_data2, 0); // M=0: ricerca minimo
                max = PRINT_q_in_intervallo(s_p, temp_data, temp_data2, 1); // M=1: ricerca massimo
                printf("quotazioni per %s, tra le date %d/%d/%d - %d/%d/%d:  MIN = %f  MAX = %f", temp_str, temp_data.year, temp_data.month, temp_data.day, temp_data2.year, temp_data2.month, temp_data2.day, min, max);
                printf("\n\n");
                
                break;
                
            case 5:
                
                printf("inserisci titolo azionario: "); temp_str = calloc(1, sizeof *temp_str);
                scanf("%s", temp_str); INSERT_title_stock(s_p, temp_str);
                s_p = SEARCH_in_list(s_p, s_list);
                temp_data.year=0; temp_data.month=0; temp_data.day=0; temp_data2.year=9999; temp_data2.month=99; temp_data2.day=99;  // creo delle date fittizie
                min = PRINT_q_in_intervallo(s_p, temp_data, temp_data2, 0); // M=0: ricerca minimo   // le date confrontate saranno smepre nell' intervallo
                max = PRINT_q_in_intervallo(s_p, temp_data, temp_data2, 1); // M=1: ricerca massimo
                printf("quotazioni per %s:  MIN = %f  MAX = %f", temp_str, min, max);
                printf("\n\n");
                
                break;
                
            case 6:
                printf("inserisci titolo azionario e soglia: "); temp_str = calloc(1, sizeof *temp_str);
                scanf("%s%d", temp_str, &S); INSERT_title_stock(s_p, temp_str);
                s_p = SEARCH_in_list(s_p, s_list);
                min = BST_lenght_wrap2(s_p, 0);
                max = BST_lenght_wrap2(s_p, 1);
                if(max/min > S){
                    BSTbalance_wrapper(s_p, S);
                    printf("\nL'albero è stato bilanciato\n\n");
                }
                else
                    printf("L'albero non è stato bilanciato (cammino max/min > soglia)\n");
                    
                break;
                
            case 0:
                free(temp_str);
                free_list(s_list);
                free_stock_link(s_p);
                exit(EXIT_SUCCESS);
                break;
                
            default:
                printf("errore comando\n\n");
        }
    }
    
    return 0;
}

stock_list new_file(char* nome_file, stock_list s_list){
    
    FILE* fp;
    int n_temp, n_tr;
    int i, j;
    char title[20];
    date tmp, curr_tmp; int tmp_value,  tmp_n_title, curr_tmp_n_title;   curr_tmp.year=0; curr_tmp.month=0; curr_tmp.day=0;
    quotation q = Qinit(); // quotazione in una data
    stock_link temp_node;
    
    fp = fopen(nome_file, "r");
    
    if(fp==NULL){
        printf("errore apertura file\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp, "%d", &n_temp); INSERT_n_stock(n_temp, s_list);
    
    for(i=0; i<n_temp; i++){
        
        fscanf(fp, "%s%d", title, &n_tr);
        temp_node = NEW_stock_node(title, s_list, n_temp);
        
        for(j=0; j<n_tr; j++){
            
        fscanf(fp, "%d/%d/%d %d:%d %d %d", &tmp.year, &tmp.month, &tmp.day, &tmp.time.hour, &tmp.time.minute, &tmp_value, &tmp_n_title);
            
            if(is_different_date(tmp, curr_tmp)){ // j>0 serve per saltare la prima lettura (non c'è bisogno di controllare che la data letta sia la stessa della precedente)
                
                q.q_date.year = curr_tmp.year;  q.q_date.month = curr_tmp.month;  q.q_date.day = curr_tmp.day;   //     F1.txt
                if(j>0) BSTinsert_leafR_wrapper(s_list, q, temp_node);
                
                curr_tmp_n_title = 0;
                curr_tmp.year = tmp.year; curr_tmp.month = tmp.month; curr_tmp.day = tmp.day;
                q.q_date.year = 0;  q.q_date.month = 0;  q.q_date.day = 0; q.value = 0;
            }
            
            q.value = calc_quotatation(tmp_value, tmp_n_title, &curr_tmp_n_title, q.value);
        }
        
        q.q_date.year = curr_tmp.year;  q.q_date.month = curr_tmp.month;  q.q_date.day = curr_tmp.day;   //     F1.txt
        BSTinsert_leafR_wrapper(s_list, q, temp_node);
        
        curr_tmp.year=0; curr_tmp.month=0; curr_tmp.day=0;
    }
    
    fclose(fp);
    
    return s_list;
}


