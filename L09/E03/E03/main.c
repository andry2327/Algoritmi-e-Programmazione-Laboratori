//
//  main.c
//  E03
//
//  Created by Andrea Pellegrino on 05/12/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personaggi.h"

void free_p(link p);
int command_selector(char command[30]);
void init_str(char *s);

int main(int argc, const char * argv[]) {
        
        int i=0;
        char comando[30+1]; //suppongo che il comando si aal massimo 50 char
        inventario *oggetti = malloc(sizeof(inventario)); int n_oggetti;
        link PgList_head = malloc(sizeof(link)); PgList_head->pg_next=NULL;  link p = malloc(sizeof(*p));
        pg tmp; inventario* x;
        
        oggetti = leggi_inv(&n_oggetti);
        /*
        for(i=0; i<15; i++)
        printf("%s %s %d %d %d %d %d %d\n", oggetti[i].nome , oggetti[i].tipologia, oggetti[i].modificatori.hp, oggetti[i].modificatori.mp, oggetti[i].modificatori.atk, oggetti[i].modificatori.def, oggetti[i].modificatori.mag, oggetti[i].modificatori.spr); printf("\n");
        */
        PgList_head->pg_next = leggi_pg();
        /*
        for(p=PgList_head->pg_next; p!=NULL; p=p->pg_next){
            printf("%s %s %s %d %d %d %d %d %d\n", p->pg_data.codice, p->pg_data.classe , p->pg_data.nome, p->pg_data.stats.hp, p->pg_data.stats.mp, p->pg_data.stats.atk, p->pg_data.stats.def, p->pg_data.stats.mag,p->pg_data.stats.spr);
        } printf("\n");
        */
        while(1){
            
            printf("nuovo_personaggio / elimina_personaggio /  aggiungi_oggetto_pg / cancella_oggetto_pg / pg_stats / termina\n");
            printf("Inserisci comando da eseguire: ");
            scanf("%s", comando);  printf("\n");
        
            switch(command_selector(comando)){
                
                case 1:  //nuovo_personaggio
                    printf("<codice> <nome> <classe> <hp> <mp> <atk> <def> <mag> <spr>\n");
                    printf("inserisci dati nuovo personaggio nel formato soprastante:\n");
                    scanf("%s%s%s%d%d%d%d%d%d", tmp.codice, tmp.nome, tmp.classe, &tmp.stats.hp, &tmp.stats.mp, &tmp.stats.atk, &tmp.stats.def, &tmp.stats.mag, &tmp.stats.spr);
                    PgList_head->pg_next = new_node_pg(tmp, PgList_head->pg_next);
                    print_list(PgList_head);
                    break;
                
                case 2:  //elimina_personaggio
                    printf("inserisci codice del personaggio da cancellare: "); init_str(comando);
                    scanf("%s", comando);
                    p = delete_element(comando, PgList_head);
                    printf("Elemento eliminato:\n");
                    printf("%s %s %s %d %d %d %d %d %d\n", p->pg_data.codice,  p->pg_data.nome,  p->pg_data.classe,  p->pg_data.stats.hp ,  p->pg_data.stats.mp,  p->pg_data.stats.atk,  p->pg_data.stats.def, p->pg_data.stats.mag, p->pg_data.stats.spr);
                    free(p);
                    printf("\n");
                    print_list(PgList_head);
                    printf("\n");
                    
                    break;
                
                case 3:  //aggiungi_oggetto_pg
                    printf("inserisci codice del personaggio a cui aggiungere un oggetto: "); init_str(comando);
                    scanf("%s", comando);
                    p = find_pg(comando, PgList_head, 0);  // restituisce il puntatore al personaggio a cui aggiungere un oggetto
                    printf("inserisci nome dell'oggetto da aggiungere all'equipaggiamento di %s: ", p->pg_data.nome); init_str(comando);
                    scanf("%s", comando);
                    add_ogg_pg(comando, oggetti, n_oggetti, p);
                    printf("Inventario attuale di %s:\n\n", p->pg_data.nome);
                    for(x=p->pg_data.eqip.eqip[i]; x!=NULL; x=p->pg_data.eqip.eqip[i]){
                        printf("%s %s\n", x->nome, x->tipologia);
                        i++;
                    }
                    printf("\n\n");
                    
                    break;
                                
                case 4:  //cancella_oggetto_pg
                    printf("inserisci codice del personaggio a cui cancellare un oggetto: "); init_str(comando);
                    scanf("%s", comando);
                    p = find_pg(comando, PgList_head, 0);  // restituisce il puntatore al personaggio a cui aggiungere un oggetto
                    printf("\nInventario attuale di %s:\n\n", p->pg_data.nome);
                    for(x=p->pg_data.eqip.eqip[i]; x!=NULL; x=p->pg_data.eqip.eqip[i]){
                        printf("%s %s\n", x->nome, x->tipologia);
                        i++;
                    }
                    printf("\ninserisci nome dell'oggetto da cancellare dall'equipaggiamento di %s: ", p->pg_data.nome); init_str(comando);
                    scanf("%s", comando);
                    delete_ogg_pg(comando, oggetti, n_oggetti, p);
                    printf("\nInventario attuale di %s:\n\n", p->pg_data.nome);
                    for(x=p->pg_data.eqip.eqip[i]; x!=NULL; x=p->pg_data.eqip.eqip[i]){
                        printf("%s %s\n", x->nome, x->tipologia);
                        i++;
                    }
                    printf("\n\n");
                    
                    break;
                    
                case 5:  //pg_stats
                    p = malloc(sizeof(*p));
                    //free(p);
                    printf("inserisci codice del personaggio di cui vedere le statistiche: "); init_str(comando);
                    scanf("%s", comando);
                    p = find_pg(comando, PgList_head, 0);
                    calc_stats_pg(p);
                    printf("\n\n");
                    break;
                
                case 0:
                    free_p(PgList_head);
                    free(p);
                    exit(EXIT_SUCCESS);
            
                default: free_p(PgList_head); printf("comando errato\n");
            }
            
        }
        
        return 0;
    }

void free_p(link h){
    
    link x, p;
    
    for(x=h->pg_next, p=h; (x!=NULL); p=x, x=x->pg_next){
        free(p);
    }
    free(x);
}

int command_selector(char command[30]){
        
    if(strcmp(command, "nuovo_personaggio")==0)
        return 1;
    if(strcmp(command, "elimina_personaggio")==0)
        return 2;
    if(strcmp(command, "aggiungi_oggetto_pg")==0)
        return 3;
    if(strcmp(command, "cancella_oggetto_pg")==0)
        return 4;
    if(strcmp(command, "pg_stats")==0)
        return 5;
    if(strcmp(command, "termina")==0)
        return 0;
        
    return -1;
}

void init_str(char *s){
    
    int i;
    
    for(i=0; i<51; i++)
        s[i] = '\0';
}
