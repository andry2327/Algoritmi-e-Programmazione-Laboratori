//
//  main.c
//  ES2
//
//  Created by Andrea Pellegrino on 20/10/2020.
//

#include <stdio.h>
#include <string.h>
#define DIM 16
#define BIT_MAX 128

int isbigEndian(int n);
void init_str(unsigned char s[31]);
void init_int(int bits[BIT_MAX]);
void stampaCodifica (void *p, int size, int bigEndian);
void int_to_binary (unsigned char hex[DIM+1], int size, int bigEndian);
void print_bits( int size, int esp, int u, int bits[BIT_MAX]);

int main(int argc, const char * argv[]) {
    
    int bigEndian;
    float af;
    double ad;
    long double ald;
    int endianess_test = 323; // Hex: 143
    
    bigEndian = isbigEndian(endianess_test);
    
    bigEndian? printf("il sistema e' Big endian\n") : printf("il sistema e' Little endian endian\n");
    printf("\n");
    
    printf("la variabile 'af' e' grande %d byte (%d bit)\n", (int)sizeof(af), (int)(8*sizeof(af))); // 1 byte = 8 bit
    printf("la variabile 'ad' e' grande %d byte (%d bit)\n", (int)sizeof(ad), (int)(8*sizeof(ad)));
    printf("la variabile 'ald' e' grande %d byte (%d bit)\n", (int)sizeof(ald), (int)(8*sizeof(ald)));
    printf("\n");
    
    printf("inserisci numero:\n");
    scanf("%f", &af);
    ad = (double)af;
    ald = (long double)af;
    
    printf("\n\n");
    
    printf("af (FLOAT): %f", af);
    printf("\n");
    stampaCodifica((void *)&af, sizeof(af), bigEndian);
    printf("\n");
    printf("ad (DOUBLE): %f", af);
    printf("\n");
    stampaCodifica((void *)&ad, sizeof(ad), bigEndian);
    printf("\n");
    printf("ald (LONG DOUBLE): %lf", af);
    printf("\n");
    stampaCodifica((void *)&ald, sizeof(ald), bigEndian);
    
    return 0;
}

int isbigEndian(int n){
    
    unsigned char *pt;
    
    pt = (unsigned char*)&n;  //323 in hex = 143
    
    if ((int)*pt == 67) // 43 in Hex = 67 in Decimale
        return 0;   //se nel 1° byte indirizzazto da *pt è presente 43 (67 in decimale) il calcolatore utlizza la codifica little Endian (LSB su byte piu basso)
    else
        return 1; //is little Endian = TRUE
    
    return 0;
}

void stampaCodifica (void *p, int size, int bigEndian){
    
    unsigned char num[DIM+1];
    int i;
    unsigned char *c;
    
    c = p;
    
    init_str(num);
    
    for (i=0; i<size; i++){
        num[i] = *(c+i);
    }
    
    printf("\n");
    
    for (i=0; i<size; i++){
        printf("*(p+i):%d  %.2X \n",i, num[i]);
    }
    printf("\n"); //1000011 10011100 1000111 1111100
    
    printf("i byte dal più al meno significativo sono: ");
    for (i=0; i<size; i++){
        printf("%X", num[ bigEndian?i : size-i-1 ]);
        }
    
    printf("\n");
    
    int_to_binary(num, size, bigEndian);
    
    }

void init_str(unsigned char s[DIM+1]){
    
    int i;
    
    for(i=0; i<DIM; i++)
        s[i] = '\0';
}

void init_int(int bits[BIT_MAX]){

    int i;
    
    for(i=0; i<BIT_MAX; i++)
        bits[i] = 0;
}

void int_to_binary (unsigned char hex[DIM+1], int size, int bigEndian){
    
    /*per semplicità, per trasformare hex in binario, passo per la trasformazione ad intero*/
    int i, j, l=0, m, u=0;
    int t_l=0, t_u=0, *p_tl, *p_tu;
    int t_bit;
    float n;
    int hex_to_int[DIM];
    int bit[BIT_MAX];  init_int(bit); //inizializzo le celle del vettore a 0
    
    p_tl = &t_l;
    p_tu = &t_u;
    
    for(i=0; i<size; i++){
        hex_to_int[i] = (int)hex[ bigEndian?i : size-i-1 ];
    }
    
    printf("\n");
    i=0;
    
    /* converto ogni byte da int a bianrio*/
    
    for(j=0; j<size; j++){
        n = hex_to_int[j];
        l = *p_tl;
        i=0;
        while(n != 0){
        
            bit[l+i] = (int)n % 2;
            n = (int)(n/2);
            i++;
        }
        
        u = l + i;
        
        for(m=0; m<(int)(u-l)/2; m++){  //inverto l'ordine dei bit appena letti all'interno del vettore
            t_bit = bit[l+m];
            bit[l+m] = bit[u-m-1];
            bit[u-m-1] = t_bit;
        }
        
        printf("%X --> ", hex[ bigEndian?j : size-j-1 ]);
        printf("%d: ", hex_to_int[j]);
        for(i=l; i<u; i++)
            printf("%d", bit[i]);
        printf("\n");
        
        *p_tl = u;
    }
    
    printf("\n");
    
    if (size == 4){                   //float
        print_bits(size, 8, u, bit);
    }else if (size == 8){             //double
        print_bits(size, 11, u, bit);
    }else if (size == 16){            //long double
        print_bits(size, 15, u, bit);
    }
    
    printf("\n");

}

void print_bits(int size, int esp, int u, int bits[BIT_MAX]){
    
    int i, j;
    
    printf("bit esponente: ");
    for(i=0; i<esp; i++)
        printf("%d", bits[i]);
    printf("\n");
    printf("bit mantissa: ");
    for(j=i; j<u+(size*8-u)-1; j++)
        printf("%d", bits[j]);
    printf("\n");
}
