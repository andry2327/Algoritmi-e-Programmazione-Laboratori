//
//  inventario.h
//  E03
//
//  Created by Andrea Pellegrino on 05/12/20.
//

#ifndef inventario_h
#define inventario_h

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

inventario* leggi_inv(int* n_oggetti);
inventario* find_ogg(char* s, inventario* inv);
void print_ogg(inventario* inv);

#endif /* inventario_h */
