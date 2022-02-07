//
//  main.c
//  Lab00_1
//
//  Created by Andrea Pellegrino on 01/10/2020.
//

#include <stdio.h>
#define N 10

int main(int argc, const char * argv[]) {
    
    int v[N];
    int i=0;
    int j=0;
    int k=0;
    int i_last = -1;
    int len;
    int max_len = 0;
    int flag = 0;
    
    
    printf("inserisci le componenti del vettore:\n");
    
    for(i=0;i<N;i++){
        
        printf("p%d:", i);
        scanf("%d", &v[i]);
    }
    
    printf("\nilvettore e': ");
    
    for(i=0;i<N;i++){
        
        printf("%d ", v[i]);
    }
    
    for(i=0;i<N;i++){
        if(v[i] == 0){
            len = i - i_last -1;
            i_last = i;
            if (len > max_len){
                max_len = len;
            }
        }
    }
    
    if(i - i_last > max_len){
        
        max_len = i - i_last - 1;
    }
    
    printf("\nmax_len = %d\n", max_len);
    
    int v_max[max_len];
    
    for (i = 0; i < N-max_len + 1; i++){
        for(j = 0; j < max_len; j++){
            v_max[j] = v[j+i];
            if (v_max[j] == 0){
                flag = 1;
            }
        }
        
        if (flag == 0){
            for(k = 0; k < max_len; k++){
                
                printf("%d ", v_max[k]);
            }
            printf("\n");
        }
        flag = 0;
        
    }
    
    printf("\n");
    
    return 0;
}


