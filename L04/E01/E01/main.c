//
//  main.c
//  E01
//
//  Created by Andrea Pellegrino on 26/10/2020.
//

#include <stdio.h>

void swap(int *p_a, int *p_b);
int is_odd(int n); // 1 if dispari, 0 if pari
int gcd(int a, int b);

int main(int argc, const char * argv[]) {
    
    int a, b;
    
    printf("inserisci due numeri (a>b):\n");
    scanf("%d %d", &a, &b);
    
    if (a<b)
        swap(&a, &b);
    
    printf("gdc: %d", gcd(a, b));
    printf("\n\n");
    
    return 0;
}

int gcd(int a, int b){
    
    if (a<b)
        swap(&a, &b);
    
    if (b == 0) // 1 condizione di terminazione: gcd (a = (int)n, 0) = a
        return a;
    
    if (a == b) // 2 condizione di terminazione gcd (a = (int)n, b = (int)m) = a = b
        return a;
    
    if (!is_odd(a) && !is_odd(b)) // a, b pari
        return 2*gcd(0.5*a, 0.5*b);
        
    else if(is_odd(a) && !is_odd(b))  //a dispari, b pari
        return gcd(a, 0.5*b);
        
    else if(is_odd(a) && is_odd(b))  //a, b dispari
        return gcd((a-b)*0.5, b);
        
    else if(!is_odd(a) && is_odd(b)) //a pari, b dispari
        return gcd(0.5*a, b);
    
    else
        return 1;
    
}

void swap(int *p_a, int *p_b){
    
    int t;
    
    t = *p_a;
    *p_a = *p_b;
    *p_b = t;
}

int is_odd(int n){
    
    return n % 2;
}
