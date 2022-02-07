//
//  main.c
//  E01
//
//  Created by Andrea Pellegrino on 30/11/20.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct att{
    
    int s;
    int f;
}att;

void attSel(int N, att* v);

att* C_sempl(int pos, att* v, att* sol, att* sol1, int n, int k, int start, int count, int max, int* d1);

int is_compatibile(att curr, att* sol, int dim);

int main(int argc, const char * argv[]) {
    
    FILE* fp;
    int n_righe;
    int i;
    att* v;
    
    fp = fopen("att.txt","r");
    
    if(fp==NULL){
        printf("errore apertura file\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp, "%d", &n_righe);
    
    v = malloc(n_righe*sizeof(*v));
    
    for(i=0; i<n_righe; i++)
        fscanf(fp, "%d%d", &v[i].s, &v[i].f);
    
    attSel(n_righe, v);
    
    fclose(fp);
    
    return 0;
}

void attSel(int N, att* v){
    
    int i, j; int k_max=0;
    att* sol=NULL;
    int d_max=0; att* sol_max=malloc(N*sizeof(*sol_max));
    int d1=0; att* sol1=malloc(N*sizeof(*sol1));
    
    
    for(i=1; i<=N; i++){
        
        sol = malloc(i*sizeof(*sol));
        
        sol1 = C_sempl(0, v, sol, sol1, N, i, 0, 0, 0, &d1);
        
        if(d1 > d_max){
            k_max=i;
            for(j=0; j<i; j++){
                
                sol_max[j].s = sol1[j].s;
                sol_max[j].f = sol1[j].f;
            }
            d_max = d1;
        }
        free(sol);
    }
    
    printf("soluzione trovata, diff. max = %d:\n\n", d_max);
    
    for(i=0; i<k_max; i++)
        printf("%d %d\n", sol_max[i].s, sol_max[i].f);
    printf("\n\n");
    
    free(sol_max);  free(sol1);
}

att* C_sempl(int pos, att* v, att* sol, att* sol1, int n, int k, int start, int count, int max, int* d1){
    
    int i;
    
    if(pos>=k){
        if(max>*d1){
            *d1 = max;
            for(i=0; i<pos; i++){
                sol1[i].s = sol[i].s;
                sol1[i].f = sol[i].f;
            }
            //sol1 = sol;
        }
        return sol1;
    }
    
    for(i=start; i<n; i++){
        
        if(pos==0?1:is_compatibile(v[i], sol, pos)){
        
            sol[pos] = v[i];
            max += v[i].f - v[i].s;
        
            sol1 = C_sempl(pos+1, v, sol, sol1, n, k, start+1, count, max, d1);
        
            max -= v[i].f - v[i].s;
            
        }
    }
    
    return sol1;
}

int is_compatibile(att curr, att* sol, int dim){
    
    int i;
    
    for(i=0; i<dim; i++){
        if( (sol[i].s < curr.f) &&  (curr.s < sol[i].f) )
            return 0;
    }
    return 1;
}
