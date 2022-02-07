//
//  main.c
//  E01
//
//  Created by Andrea Pellegrino on 07/12/20.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct att{
    
    int s;
    int f;
    int dmax;
    int last_p;
}att;

att* leggi_v(att *v, int* n, int* d_max, int* p_last);

int is_compatibile(att *v, int i, int j);

void print_sol(att *v, int i);

int main(int argc, const char * argv[]) {
    
    int n_righe; int i, j;
    int d_j, d_i;
    int d_max, p_last;
    att* v=NULL;
    
    v = leggi_v(v, &n_righe, &d_max, &p_last);
    
    /*
    for(i=0; i<n_righe; i++)
        printf("%d %d, d: %d, %d\n", v[i].s, v[i].f, v[i].i_dmax, v[i].last_p);
        */
    
    for(i=1; i<n_righe; i++){
        d_i = v[i].f - v[i].s;
        for(j=0; j<i; j++){
            
            d_j = v[j].f - v[j].s;
            
            if( (is_compatibile(v, i, j)) && (v[j].dmax > (v[i].dmax-d_i)) ){
                
                v[i].dmax = d_i + v[j].dmax;
                v[i].last_p = j;
            }
        }
        
        if(v[i].dmax > d_max){
            
            d_max = v[i].dmax;
            p_last = i;
        }
    }
    
    printf("soluzione trovata, diff. max = %d:\n\n", d_max);
    
    print_sol(v, p_last);

    
    return 0;
}

int is_compatibile(att *v, int i, int j){
    
    if( (v[j].s < v[i].f) &&  (v[i].s < v[j].f) )
        return 0;

    return 1;
}

att* leggi_v(att *v, int* n, int* d_max, int* p_last){
    
    FILE* fp;
    int i;
    
    fp = fopen("att1.txt","r");
    
    if(fp==NULL){
        printf("errore apertura file\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp, "%d", n);
    
    v = malloc((*n)*sizeof(*v));
    
    for(i=0; i<*n; i++){
        
        fscanf(fp, "%d%d", &v[i].s, &v[i].f);
        v[i].dmax = v[i].f - v[i].s;  // salvo la durata dell' attività i
        v[i].last_p = -1; // inizializzo la posizione dell' elemento precedente a -1
        
        if(v[i].dmax > *d_max){
            *d_max = v[i].dmax;  // inizializzo già durante la lettura file quale sia la differenza massima, in modo che venga stampata essa nel caso nessun orario sia compatibile con nessun altro
            *p_last = i;  // analogamente per la posizione dell'attività con differenza massima
        }
    }
    
    return v;
}

void print_sol(att *v, int i){
    
    if (v[i].last_p==-1) {
        printf("%d %d\n", v[i].s, v[i].f);
        return;
    }
    
  print_sol(v, v[i].last_p );
    
  printf("%d %d\n\n", v[i].s, v[i].f);
}
