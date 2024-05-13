#include <stdio.h>
#include <stdlib.h>

#define UPPER_BOUND 10000000

void siv_up(_Bool* array_map, long start_index) {
    for(long i = start_index*2; i < UPPER_BOUND; i+= start_index) {
        array_map[i] = 1;
    }
}

void prime_siv(_Bool* array_map) {
    array_map[0] = 1;
    array_map[1] = 1;
    for(long i = 2; i< UPPER_BOUND; i++) {
        if(array_map[i] == 0) {
            siv_up(array_map, i);
        }
    }
}

int main(int argc, char *argv[]) {
    _Bool array_map[UPPER_BOUND] = {0};
    prime_siv(array_map);
    long i = UPPER_BOUND-1;
    while(array_map[i] == 1) {
        i = i - 1;
    }
    printf("%ld\n",i);

}