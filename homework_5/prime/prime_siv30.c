#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define UPPER_BOUND 1000000
const int MAGIC_ARRAY[] = {1,7,11,13,17,19,23,29};


typedef struct bitmap_index {
    long byte;
    short bit;
} b_i;
typedef struct lookup_add {
    long byte_offset;
    short new_bit;
    long reset_count;
} l_a;

l_a lookup[8][30];

bool in_magic(long v) {
    for(int i = 0;i < 8;i++) {
        if(MAGIC_ARRAY[i] == v) return true;
    }
    return false;
}

short in_magic_i(long v) {
    for(int i = 0;i < 8; i++) {
        if(MAGIC_ARRAY[i] == v) return i;
    }
    *((int*)0) = 42;
}

void get_add_offset(l_a* add_offset ,short bit, long offset) {
    long new_offset = MAGIC_ARRAY[bit] + offset;
    long count = 1;
    while(!in_magic(new_offset % 30)) {
        count += 1;
        new_offset += offset;
    }
    add_offset->byte_offset = new_offset / 30;
    add_offset->new_bit = in_magic_i(new_offset % 30);
    add_offset->reset_count = count;
}

void add_lookup(b_i* bindex, long v) {
    l_a* looked_up = &lookup[bindex->bit][v % 30];
    bindex->byte += (v / 30) * looked_up->reset_count + looked_up->byte_offset;
    bindex->bit = looked_up->new_bit;
}

void buildLookup() {
    for(short bit = 0;bit<8;bit++) {
        lookup[bit][0].byte_offset = 0;
        lookup[bit][0].new_bit = bit;
        lookup[bit][0].reset_count = 1;
        for(long offset = 1;offset<30;offset++) {
            get_add_offset(&lookup[bit][offset],bit,offset);
        }
    }
    for(short bit = 0;bit<8;bit++) {
        for(long offset = 0;offset<30;offset++) {
            printf("byte_offset = %ld, new_bit = %d, reset_count = %ld\n",lookup[bit][offset].byte_offset,lookup[bit][offset].new_bit,lookup[bit][offset].reset_count);
        }
    }
}

int calculate_primes() {
    _Bool array_map[UPPER_BOUND/8] = {0};
    long i = UPPER_BOUND-1;
    printf("%ld\n",i);

}

int main(int argc, char *argv[]) {
    buildLookup();
    // printf("%d\n",in_magic_i(17));
    // for(int i = 0;i<100;i++) {
    //     calculate_primes();
    // }
}