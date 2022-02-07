//
//  main.c
//  E02
//
//  Created by Andrea Pellegrino on 02/12/20.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct tube{
    
    char color;
    int val;
}tube;

typedef struct tiles{
    
    tube t1;
    tube t2;
    int rot; // 1: ruotata, 0: non ruotata
    int used; //1: tessera usata, 0: tessera non usata
}tiles;

tiles* leggi_tessere(int* n);
tiles** leggi_board(tiles* tessere, int* R, int* C);

int punteggio(tiles** board, int dim, int C);
int D_sempl(int pos, tiles* tessere, tiles** board, int dim, int C, tiles** max_board, int n, int max_points);
void rot(tiles**board, int pos);
void free2(tiles* tessere, tiles** board, int dim_b);
void print_board(tiles** board, int C, int dim);

int main(int argc, const char * argv[]) {
    
    tiles* tessere; int n_tessere; int i;
    tiles** board=NULL; int R, C; //consideroo la board come un vettore di dimensione RxC, accendo alla riga e colonna tramite: i=pos/C, j=pos%C
    int dim;
    tiles** max_board = NULL;
    
    tessere = leggi_tessere(&n_tessere);
    /*
    for(i=0; i<n_tessere; i++)
        printf("%c %d %c %d %d %d\n", tessere[i].t1.color, tessere[i].t1.val, tessere[i].t2.color, tessere[i].t2.val, tessere[i].rot, tessere[i].used);
    */
    board = leggi_board(tessere, &R, &C); dim = R * C;
    
    max_board = malloc(dim*sizeof(**max_board));
    for(i=0; i<dim; i++){
        max_board[i] = malloc(dim*sizeof(*max_board));
    }
    /*
    for(i=0; i<dim; i++){
        
        if(board[i]==NULL)
            printf("board[%d]: NULL\n", i);
        else
            printf("board[%d]: %c %d %c %d %d %d\n", i, board[i]->t1.color, board[i]->t1.val, board[i]->t2.color, board[i]->t2.val, board[i]->rot, board[i]->used);
    }*/
     
    printf("soluzione massima trovata, punteggio: %d\n\n", D_sempl(0, tessere, board, dim, C, max_board, n_tessere, 0));
    
    print_board(max_board, C, dim);
    
    printf("\n\n");
    
    //free2(tessere, board, dim);
    free(max_board);
    
    return 0;
}

int D_sempl(int pos, tiles* tessere, tiles** board, int dim, int C, tiles** max_board, int n, int max_points){
    
    int i, p;
    
    if(pos>=dim){ //print_board(board, C, dim);
        p = punteggio(board, dim, C);
        if(p > max_points){
            max_points = p;
            for(i=0; i<dim; i++){
                max_board[i]->t1.color = board[i]->t1.color; max_board[i]->t2.color = board[i]->t2.color;
                max_board[i]->t1.val = board[i]->t1.val; max_board[i]->t2.val = board[i]->t2.val;
                max_board[i]->rot = board[i]->rot;
            }
        }
        return max_points;
    }
    
    if(board[pos]==NULL){
        for(i=0; i<n; i++){
            if(tessere[i].used==0){
                board[pos] = tessere + i; //print_board(board, C, dim);
                board[pos]->used = 1;
                max_points = D_sempl(pos+1, tessere, board, dim, C, max_board, n, max_points);
                rot(board, pos); //considero il caso di tessera ruoatata e cerco se ce un punteggio max
                //print_board(board, C, dim);
                max_points = D_sempl(pos+1, tessere, board, dim, C, max_board, n, max_points);
                rot(board, pos); // riposrto la casella nella posizione originale letta dal file
                board[pos]->used = 0; board[pos]->rot = 0;
                board[pos] = NULL; // backtrack
            }
        }
    }else
        max_points = D_sempl(pos+1, tessere, board, dim, C, max_board, n, max_points);
        
    return max_points;
}

tiles* leggi_tessere(int* n){
    
    FILE* fp;
    
    tiles* tessere1=NULL;
    int i;
    
    fp = fopen("tiles.txt","r");
    
    if(fp==NULL){
        
        printf("errore apertura file 'tiles.txt'\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp, "%d\n", n);
    
    tessere1 = malloc((*n)*sizeof(*tessere1));
    
    for(i=0; i<*n; i++){
        
        fscanf(fp, "%c %d %c %d\n", &tessere1[i].t1.color, &tessere1[i].t1.val, &tessere1[i].t2.color, &tessere1[i].t2.val);
        tessere1[i].rot = 0; tessere1[i].used = 0;
    }
    
    return tessere1;
}

tiles** leggi_board(tiles* tessere, int* R, int* C){
    
    FILE* fp;
    tiles** board1;
    int dim, tess, is_rot;
    int i;
    
    fp = fopen("board.txt","r");
    
    if(fp==NULL){
        
        printf("errore apertura file 'board.txt'\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp, "%d%d\n", R, C); dim = (*R) * (*C);
    
    board1 = malloc(dim*sizeof(**board1));
    for(i=0; i<dim; i++){
        board1[i] = malloc(dim*sizeof(*board1));
    }
    
    for(i=0; i<dim; i++){
        
        fscanf(fp, "%d/%d", &tess, &is_rot);
        
        if( (tess==-1) && (is_rot==-1) )
            board1[i] = NULL;
        
        else{
            board1[i] = tessere + tess;
            if(is_rot==1)
                rot(board1, i);
            board1[i]->used = 1;
        }
    }
    
    return board1;
}

int punteggio(tiles** board, int dim, int C){
    
    int points=0;
    int i=0, j=1;
    int flag=1;
    tube t;
    /*
    for(i=0; i<dim; i++){
        
        printf("%c %d %c %d , r: %d   ", board[i]->t1.color, board[i]->t1.val, board[i]->t2.color, board[i]->t2.val, board[i]->rot);
        if((i+1)%C==0)
            printf("\n");
    }i=0;
    */
    //print_board(board, C, dim);
    //controllo su tubi orizzontali
    
    while(i<dim){
        t.color = board[i]->t1.color;
        t.val = board[i]->t1.val;
        while((j<C) && flag){ //printf("confronto %c %c", board[i+j]->t1.color, t.color);
            if(board[i+j]->t1.color == t.color){
                t.val += board[i+j]->t1.val;
                j++;
            }
            else{
                flag=0;
                t.val=0;
            }
        }
        flag=1;
        points += t.val;
        i+=C; j=1;
    }
    
    i=0; j=C;
    
    // controllo su tubi verticali
    
    while(i<C){
        t.color = board[i]->t2.color;
        t.val = board[i]->t2.val;
        while((j<dim) && flag){ //printf("confronto %c %c", board[i+j]->t2.color, t.color);
            if(board[i+j]->t2.color == t.color){
                t.val += board[i+j]->t2.val;
                j+=C;
            }
            else{
                flag=0;
                t.val=0;
            }
        }
        flag=1;
        points += t.val;
        i++; j=C;
    }
    return points;
}

void rot(tiles** board, int pos){
    
    tube t;
    
    t = board[pos]->t1;
    board[pos]->t1 = board[pos]->t2;
    board[pos]->t2 = t;
    board[pos]->rot = 1;
}

void free2(tiles* tessere, tiles** board, int dim_b){
    
    int i;
    
    free(tessere);
    
    for(i=0; i<dim_b; i++){
        if(board[i]!=NULL)
            free(board+i);
    }
    free(board);
}

void print_board(tiles** board, int C, int dim){
    
    int i;
    
    for(i=0; i<dim; i++){
        
        if(board[i]!=NULL)
            printf("%c %d %c %d r: %d   ", board[i]->t1.color, board[i]->t1.val, board[i]->t2.color, board[i]->t2.val, board[i]->rot);
        else
            printf("        NULL        ");
        
        if((i+1)%C==0)
            printf("\n");
    }
    printf("\n\n");
}
