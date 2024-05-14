// This is just a prime siv except it only stores every other bit
// Since most primes are not even.
// This algorithm actually ended up being twice as fast as the regular prime_siv

#include <stdio.h>
#include <stdlib.h>


#define UPPER_BOUND 1000000

void siv_up(_Bool* array_map, long start_index) {
    int jump = start_index * 2 + 1;
    for(long i = start_index + jump; i < UPPER_BOUND / 2; i+= jump) {
        array_map[i] = 1;
    }
}

void prime_siv(_Bool* array_map) {
    array_map[0] = 1;
    array_map[1] = 1;
    for(long i = 2; i< UPPER_BOUND / 2; i++) {
        if(array_map[i] == 0) {
            siv_up(array_map, i);
        }
    }
}

void calculate_primes() {
    _Bool array_map[UPPER_BOUND / 2] = {0};
    prime_siv(array_map);
    long i = (UPPER_BOUND/2)-1;
    while(array_map[i] == 1) {
        i = i - 1;
    }
    printf("%ld\n",i*2 + 1);
}

int main(int argc, char *argv[]) {
    for(int i = 0;i<100;i++) {
        calculate_primes();
    }
}