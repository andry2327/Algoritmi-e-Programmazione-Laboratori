//
//  main.c
//  E03
//
//  Created by Andrea Pellegrino on 25/11/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct points{
    
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
    
}points;

typedef struct inventario{
    
    char nome[50+1];
    char tipologia[50+1];
    points modificatori;
    
}inventario;

typedef struct equipaggiamneto{
    
    inventario* in_uso;
    inventario* eqip[8];
    
}equipaggiamento;

typedef struct pg{
    
    char codice[6+1];
    char nome[50+1];
    char classe[50+1];
    equipaggiamento eqip;
    points stats;

}pg;

typedef struct nodePg *link;

typedef struct nodePg{
    
    pg pg_data;
    link pg_next;
    
}nodePg;

void free_p(link p);
int command_selector(char command[30]);
void print_list(link p);
void init_str(char *s);

inventario* leggi_inv(int* n_oggetti);
link leggi_pg(void);
link new_node_pg(pg pg, link next);
link delete_element(char* s, link h);
link find_pg(char* s, link h);
void add_ogg_pg(char* s, inventario* p, int n_oggetti, link pg);
void delete_ogg_pg(char* s, inventario* p, int n_oggetti, link pg);
void calc_stats_pg (link pg);



int main(int argc, const char * argv[]) {
    
    int i=0;
    char comando[30+1]; //suppongo che il comando si aal massimo 50 char
    inventario *oggetti = malloc(sizeof(inventario)); int n_oggetti;
    link PgList_head = malloc(sizeof(link)); PgList_head->pg_next=NULL;  link p = malloc(sizeof(*p));
    pg tmp; inventario* x;
    
    oggetti = leggi_inv(&n_oggetti);
    
    for(i=0; i<15; i++)
    printf("%s %s %d %d %d %d %d %d\n", oggetti[i].nome , oggetti[i].tipologia, oggetti[i].modificatori.hp, oggetti[i].modificatori.mp, oggetti[i].modificatori.atk, oggetti[i].modificatori.def, oggetti[i].modificatori.mag, oggetti[i].modificatori.spr); printf("\n");
    
    PgList_head->pg_next = leggi_pg();
    
    for(p=PgList_head->pg_next; p!=NULL; p=p->pg_next){
        printf("%s %s %s %d %d %d %d %d %d\n", p->pg_data.codice, p->pg_data.classe , p->pg_data.nome, p->pg_data.stats.hp, p->pg_data.stats.mp, p->pg_data.stats.atk, p->pg_data.stats.def, p->pg_data.stats.mag,p->pg_data.stats.spr);
    } printf("\n");
    
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
                p = find_pg(comando, PgList_head);  // restituisce il puntatore al personaggio a cui aggiungere un oggetto
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
                p = find_pg(comando, PgList_head);  // restituisce il puntatore al personaggio a cui aggiungere un oggetto
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
                p = find_pg(comando, PgList_head);
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






inventario* leggi_inv(int* n_oggetti){
    
    FILE* fp_inv;
    int n_righe; int i=0;
    inventario* inv;
 

    fp_inv  = fopen("inventario.txt", "r");
  
    
    if(fp_inv==NULL){
        printf("errore apertura file inventario\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp_inv, "%d", &n_righe); *n_oggetti = n_righe;
    
    inv = malloc(n_righe*sizeof(inventario));
    
    while(fscanf(fp_inv, "%s%s%d%d%d%d%d%d\n", inv[i].nome , inv[i].tipologia,  &inv[i].modificatori.hp, &inv[i].modificatori.mp, &inv[i].modificatori.atk, &inv[i].modificatori.def, &inv[i].modificatori.mag, &inv[i].modificatori.spr) != EOF){
        
        i++;
    }
    
    fclose(fp_inv);
    
    return inv;
}

link leggi_pg(void){
    
    FILE* fp_pg;
    pg tmp;
    link head = malloc(sizeof(*head)); head->pg_next=NULL;
    
    fp_pg  = fopen("pg.txt", "r");
  
    if(fp_pg==NULL){
        printf("errore apertura file personaggi\n");
        exit(EXIT_FAILURE);
    }
    
    while(fscanf(fp_pg, "%s%s%s%d%d%d%d%d%d\n", tmp.codice, tmp.nome, tmp.classe, &tmp.stats.hp, &tmp.stats.mp, &tmp.stats.atk, &tmp.stats.def, &tmp.stats.mag, &tmp.stats.spr) != EOF){
        
        head->pg_next = new_node_pg(tmp, head->pg_next);
    }
    
    fclose(fp_pg);
    
    return head->pg_next;
}

link new_node_pg(pg pg, link next){
    
    link x = malloc(sizeof(*x)); x->pg_next=NULL; int i;
    
    if(x==NULL){
        return NULL;
    }
    
    x->pg_next = next;  //inserzione in testa
    x->pg_data = pg;    //
    
    x->pg_data.eqip.in_uso=NULL ;
    for(i=0; i<8; i++){
        x->pg_data.eqip.eqip[i]=NULL;
    }
    
    return x;
}

link delete_element(char* s, link h){
    
    link x = NULL, p = NULL;
    
    for(x=h->pg_next, p=h; (x!=NULL) && (strcmp(s, x->pg_data.codice)!=0); p=x, x=x->pg_next);
    
    //free(p->pg_next);
    
    p->pg_next = x->pg_next;
   
    return x;
}

link find_pg(char* s, link h){
    
    link x = NULL, p = NULL;
    
    for(x=h->pg_next, p=h; (x!=NULL) && (strcmp(s, x->pg_data.codice)!=0); p=x, x=x->pg_next);
    
    return x;
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

void print_list(link PgList_head){
    
    link p = malloc(sizeof(link));
    
    for(p = PgList_head->pg_next; p!=NULL; p=p->pg_next){
        printf("%s %s %s %d %d %d %d %d %d\n", p->pg_data.codice, p->pg_data.classe , p->pg_data.nome, p->pg_data.stats.hp, p->pg_data.stats.mp, p->pg_data.stats.atk, p->pg_data.stats.def, p->pg_data.stats.mag,p->pg_data.stats.spr);
    }
}

void init_str(char *s){
    
    int i;
    
    for(i=0; i<51; i++)
        s[i] = '\0';
}

void add_ogg_pg(char* s, inventario* p, int n_oggetti, link pg){
    
    int i; inventario* p1=NULL; int flag = 1;
    
    for(i=0; (i<n_oggetti) && (flag); i++){
        if(strcmp(p[i].nome, s)==0){
            p1 = &p[i];
            flag = 0;
        }
    }
    
    flag=1;
        
    for(i=0; (i<8) && flag; i++){
        if(pg->pg_data.eqip.eqip[i] == NULL){
            pg->pg_data.eqip.eqip[i] = p1;
            printf("\nElemento %s aggiunto all' inventario di %s, equipaggiamento attuale:\n", s, pg->pg_data.nome);
            flag = 0;
        }else if(strcmp(pg->pg_data.eqip.eqip[i]->nome, s)==0){
            printf("\noggetto già esistente nell'inventario di %s\n", pg->pg_data.nome);
            return ;
        }
    }
}

void delete_ogg_pg(char* s, inventario* p, int n_oggetti, link pg){
    
    int i; int flag = 1;
    
    for(i=0; (i<n_oggetti) && flag; i++){
        if(strcmp(pg->pg_data.eqip.eqip[i]->nome, s) == 0){
            pg->pg_data.eqip.eqip[i] = NULL;
            printf("\nElemento %s cancellato dall' inventario di %s, equipaggiamento attuale:\n", s, pg->pg_data.nome);
            flag = 0;
        }
    }
    
    if(flag==1){
        printf("\noggetto da cancellare non trovato\n");
    }
}

void calc_stats_pg (link pg){
    
    int st[6];
    int i=0;
    inventario* x;
    
    st[0] = pg->pg_data.stats.hp;
    st[1] = pg->pg_data.stats.mp;
    st[2] = pg->pg_data.stats.atk;
    st[3] = pg->pg_data.stats.def;
    st[4] = pg->pg_data.stats.mag;
    st[5] = pg->pg_data.stats.spr;
    
    for(x=pg->pg_data.eqip.eqip[i]; x!=NULL; x=pg->pg_data.eqip.eqip[i]){
        
        st[0] += x->modificatori.hp;
        st[1] += x->modificatori.mp;
        st[2] += x->modificatori.atk;
        st[3] += x->modificatori.def;
        st[4] += x->modificatori.mag;
        st[5] += x->modificatori.spr;
        
        i++;
    }
    printf("\n");
    
    printf("statistiche di %s:\n\n", pg->pg_data.nome);
    
    printf("hp: %d\n", (st[0]<0)?0:st[0]);
    printf("mp: %d\n", (st[1]<0)?0:st[1]);
    printf("atk: %d\n", (st[2]<0)?0:st[2]);
    printf("def: %d\n", (st[3]<0)?0:st[3]);
    printf("mag: %d\n", (st[4]<0)?0:st[4]);
    printf("spr: %d\n", (st[5]<0)?0:st[5]);
    
    printf("\n\n");
}
