//
//  main.c
//  E02
//
//  Created by Andrea Pellegrino on 18/11/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_C 50

typedef struct Item{
    
    char codice[5+1];
    char nome[MAX_C+1];
    char cognome[MAX_C+1];
    char data_di_nascita[10+1];
    char via[MAX_C+1];
    char città[MAX_C+1];
    int cap;
}Item;

typedef struct node *link;

typedef struct node{
    
    Item data;
    link next;
}node;

void free_p(link p);
int key_greater(char *a, char *b);
int data_to_num(char *data);
void init_str(char *s);
int command_selector(char command[30]);
void print_list(link p, int w);
int data_in(char* data1, char* data_c, char* data2);

link new_node(Item data, link next);

link new_file(link p_head, int flag);

link ins_list_bySort(link h, Item nodo);

link search_by_code(char* s, link h);

link delete_element(char* s, link h);

link delete_element_by_date(char* data1, char* data2, link h, int* n);



int main(int argc, const char * argv[]) {                          //     anag1.txt
    
    link head = malloc(sizeof(link)); head->next=NULL;  //inizializzazione lista vuota: head->next=NULL
    link p=NULL, p_x=NULL;
    char d1[10+1], d2[10+1];
    int n;
    int i;
    char comando[30+1]; //suppongo che il comando si aal massimo 50 char
    
    head = new_file(head, 0);  // 0: lettura file di default, 1: per aggiunta di elementi da file
    print_list(head, 0);
    
    while(1){
        
        printf("new_element / new_elements_file /  search_by_code /  delete_element /  delete_element_by_date / print_list / termina\n");
        printf("Inserisci comando da eseguire: ");
        scanf("%s", comando);  printf("\n");
    
        switch(command_selector(comando)){
            
            case 1:  //new_element
                head = new_file(head, 1);
                print_list(head, 0);
                break;
            
            case 2:  //new_elements_file
                head = new_file(head, 0);
                print_list(head, 0);  //stampa su console
                break;
            
            case 3:  //search_by_code
                free(p);
                printf("inserisci codice da cercare: "); init_str(comando);
                scanf("%s", comando);
                p = search_by_code(comando, head);
                if(p!=NULL){
                    printf("codice trovato:\n");
                    printf("%s %s %s %s %s %s %d\n", p->data.codice,  p->data.nome,  p->data.cognome,  p->data.data_di_nascita,  p->data.via,  p->data.città,  p->data.cap);
                }else{
                    printf("codice non trovato\n");
                }
                break;
                
            case 4:  //delete_element
                free(p);
                printf("inserisci codice dell'elemento da cancellare: "); init_str(comando);
                scanf("%s", comando);
                p = delete_element(comando, head);
                printf("Elemento eliminato:\n");
                printf("%s %s %s %s %s %s %d\n", p->data.codice,  p->data.nome,  p->data.cognome,  p->data.data_di_nascita,  p->data.via,  p->data.città,  p->data.cap);
                printf("\n");
                print_list(head, 0);
                break;
                    
            case 5:  //delete_element_by-date
                free(p);
                printf("inserisci 2 date entro cui gli elementi verranno cancellati: ");
                scanf("%s %s", d1, d2);
                p = delete_element_by_date(d1, d2, head, &n);
                printf("Elementi eliminati:\n");
                for(p_x=p->next, i=0; i<n; i++, p_x=p_x->next){
                    
                    printf("%s %s %s %s %s %s %d\n", p_x->data.codice,  p_x->data.nome,  p_x->data.cognome,  p_x->data.data_di_nascita,  p_x->data.via,  p_x->data.città,  p_x->data.cap);
                    free(p_x);
                }    printf("\n");
                p->next = p_x; print_list(head, 0);
                break;
                            
            case 6:  //print_list
                print_list(head, 1);  //stampa su file
                print_list(head, 0);
                break;
            
            case 0:
                free_p(head);
                exit(EXIT_SUCCESS);
        
            default: free_p(head); printf("comando errato\n");
        }
    }
    
    return 0;
}



link new_file(link p_head, int flag){

    Item tmp;
    
    if(flag==0){  //acquisizione elementi da file
        
        FILE* fp;
        char filename[20+1];  //suppongo che il nome del file sia lungo al amssimo 20 char
    
        printf("inserisci nome file: ");
        scanf("%s", filename);
        printf("\n");
        
        fp = fopen(filename, "r");
        
        if(fp==NULL){
            printf("errore apertura file\n");
            exit(EXIT_FAILURE);
        }
        
        while(fscanf(fp, "%s%s%s%s%s%s%d\n", tmp.codice, tmp.nome, tmp.cognome, tmp.data_di_nascita, tmp.via, tmp.città, &tmp.cap) != EOF){

            p_head->next = ins_list_bySort(p_head, tmp);
        }
        
        fclose(fp);
    }
    
    else{  //acquisizione elemento da tastiera

        printf("<codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap>\n");
        printf("inserisci nuovo elemento da inserire, nel formato soprastante:");
        printf("\n");
        scanf("%s%s%s%s%s%s%d", tmp.codice, tmp.nome, tmp.cognome, tmp.data_di_nascita, tmp.via, tmp.città, &tmp.cap);
        
        p_head->next = ins_list_bySort(p_head, tmp);
        
        printf("\n");
        printf("Nuovo elemento aggiunto alla lista correttamente\n\n");
    }
    
    return p_head;
}

link ins_list_bySort(link h, Item nodo){
    
    link x = NULL, p = NULL;
    
    if((h->next)==NULL)                                            //     anag1.txt
        return new_node(nodo, h->next);
    
    for(x=h->next, p=h; (x!=NULL) && !(key_greater(nodo.data_di_nascita, x->data.data_di_nascita)); p=x, x=x->next);
    
    p->next = new_node(nodo, x);
    
    return h->next;
}

link new_node(Item data, link next){
    
    link x = malloc(sizeof(*x));
    
    if(x==NULL)
        return NULL;
    
    x->data = data;
    x->next = next;
    
    return x;
}

int key_greater(char *a, char *b){
    
    if (data_to_num(a) > data_to_num(b))
        return 1;
    return 0;
}

void print_list(link p, int w){
    
    link x;
    
    if(w==0){
        for(x=p->next; x!=NULL ; x=x->next)
            printf("%s %s %s %s %s %s %d\n", x->data.codice,  x->data.nome,  x->data.cognome,  x->data.data_di_nascita,  x->data.via,  x->data.città,  x->data.cap);
        printf("\n");
    }else{
        
        FILE *fp_print;
        
        fp_print = fopen("anagrafica.txt", "w");
        
        if(fp_print==NULL){
            printf("errore apertura file\n");
            exit(EXIT_FAILURE);
        }
        
        for(x=p->next; x!=NULL ; x=x->next)
            fprintf(fp_print, "%s %s %s %s %s %s %d\n", x->data.codice,  x->data.nome,  x->data.cognome,  x->data.data_di_nascita,  x->data.via,  x->data.città,  x->data.cap);
        
        fclose(fp_print);
        
        printf("Stampa effettuata su 'anagrafica.txt'\n");
    }
    free(x);
}

link search_by_code(char* s, link h){
    
    link x = NULL, p = NULL;
    
    for(x=h->next, p=h; (x!=NULL) && (strcmp(s, x->data.codice)!=0); p=x, x=x->next);
    
    return x;
}

void free_p(link p){
    
    if(p->next==NULL){
        free(p);
        return;
    }
    
    free_p(p->next);
    
    return;
}

link delete_element(char* s, link h){
    
    link x = NULL, p = NULL;
    
    for(x=h->next, p=h; (x!=NULL) && (strcmp(s, x->data.codice)!=0); p=x, x=x->next);
    
    p->next = x->next;
   
    return x;
}


link delete_element_by_date(char* data1, char* data2, link h, int* n1){
    
    link x = NULL, p = NULL, x_d = NULL;
    int n=0;
    
    for(x=h->next, p=h; (x!=NULL); p=x, x=x->next){
        if(data_in(data1, x->data.data_di_nascita, data2)){
            if(n==0) x_d = p;
            n += 1;
            printf("n: %d\n", n);
        }
    }
    
    *n1 = n;
    printf("*n main: %d\n", *n1);
    
    return x_d;
}

int command_selector(char command[30]){
    
    if(strcmp(command, "new_element")==0)
        return 1;
    if(strcmp(command, "new_elements_file")==0)
        return 2;
    if(strcmp(command, "search_by_code")==0)
        return 3;
    if(strcmp(command, "delete_element")==0)
        return 4;
    if(strcmp(command, "delete_element_by_date")==0)
        return 5;
    if(strcmp(command, "print_list")==0)
        return 6;
    if(strcmp(command, "termina")==0)
        return 0;
    
    return -1;
}

int data_in(char* data1, char* data_c, char* data2){
    
    if( (data_to_num(data1) < data_to_num(data_c)) && (data_to_num(data_c) < data_to_num(data2)) )
        return 1;
    return 0;
}

int data_to_num(char *data){ // questa funzione converte la data in un numero pari a anno*365 + mese*30 + giorno, per poter operare confronti (< o >) tra date in seguito
    
    int anno=0, mese=0, giorno=0;
    int i=0, j=0;
    char temp[5]; init_str(temp);
    
    while(j<2){  //giorno
        
        temp[j] = data[i];
        j++; i++;
    }
    giorno = atoi(temp);   init_str(temp); j=0;
    
    while(j<2){  //mese
        
        temp[j] = data[i+1];
        j++; i++;
    }
    mese = atoi(temp);   init_str(temp); j=0;                                     //     anag1.txt 07/12/1994 19/04/1998
    
    while(j<4){  //anno
        
        temp[j] = data[i+2];
        j++; i++;
    }
    anno = atoi(temp);  init_str(temp);
    
    return anno*365 + mese*30 + giorno;
}

void init_str(char *s){
    
    int i;
    
    for(i=0; i<5; i++)
        s[i] = '\0';
}
