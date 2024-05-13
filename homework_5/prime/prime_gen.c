#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define UPPER_BOUND 1000000
#define NUMBER_PRIMES 100000
_Bool isPrime(int pp, int* prime_list) {
    int sqrt_bound = (int)sqrt(pp) + 1;
    int i = 0;
    while(prime_list[i] <= sqrt_bound && prime_list[i] != 0) {
        if(pp % prime_list[i] == 0) {
            return false;
        }
        i = i + 1;
    }
    return true;
}

void print_primes(int* prime_list) {
    int i = 0;
    while(prime_list[i] != 0) {
        printf("%d, ",prime_list[i]);
        i = i + 1;
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int prime_list[NUMBER_PRIMES] = {0};
    int prime_count = 0;
    for(int i = 2;i<UPPER_BOUND;i++) {
        if(isPrime(i,prime_list)) {
            prime_list[prime_count] = i;
            prime_count = prime_count + 1;
            // printf("%d ",i);
        }
    }
    printf("%d\n",prime_list[prime_count-1]);

}