//
//  main.c
//  E02
//
//  Created by Andrea Pellegrino on 27/10/2020.
//

#include <stdio.h>
#define N 9

int majority (int *a, int n);

int main (int argc, const char * argv[]) {
    
    int vet[N] = {4, 2 ,4 , 4, 4, 1, 4, 6, 4}; // 1 elemento maggioritario
    int num;
    
    num = majority(vet, N);
    
    if(num != -1){
        
        printf("L'elemento maggioritario e': %d", num);
        printf("\n\n");
    }else{
        printf("Nessun elemento maggioritario");
        printf("\n\n");
    }
}

int majority(int *a, int n){
    
    int num, num1;
    int cnt = 0, cnt1 = 0;
    int i;
    
    if (n<2){
        return a[n-1];
    }
    
    num = majority(a, n/2);
    num1 = majority(a+(n/2), n-(n/2));
    
    if (num == num1){
        
        return num;
    }
    
    for(i=0; i<n; i++){
        if(num==a[i])
            cnt++;
        else if(num1==a[i])
            cnt1++;
    }
    
    if(cnt>n/2)
        return num;
    if(cnt1>n/2)
        return num1;
    
    return -1;
}

