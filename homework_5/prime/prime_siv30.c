#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define UPPER_BOUND 1000000
// Upper_Bound * (8/30)
#define UPPER_BOUND_ARY 33334
const int MAGIC_ARRAY[] = {1,7,11,13,17,19,23,29};
const unsigned char BITMASK[] = {128,64,32,16,8,4,2,1};


typedef struct bitmap_index {
    long byte;
    short bit;
} b_i;
typedef struct lookup_add {
    long byte_offset;
    short new_bit;
    long reset_count;
} l_a;

l_a lookup[8][8];

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

long to_long(b_i* bitx) {
    return bitx->byte*30 + MAGIC_ARRAY[bitx->bit];
}

void get_add_offset(l_a* add_offset ,short bit, short offset) {
    long new_offset = MAGIC_ARRAY[bit] + MAGIC_ARRAY[offset];
    long count = 1;
    while(!in_magic(new_offset % 30)) {
        // printf("%ld\n",new_offset);
        count += 1;
        new_offset += MAGIC_ARRAY[offset];
    }
    add_offset->byte_offset = new_offset / 30;
    add_offset->new_bit = in_magic_i(new_offset % 30);
    add_offset->reset_count = count;
}

void add_lookup(b_i* bindex, b_i* v) {
    l_a* looked_up = &lookup[bindex->bit][v->bit];
    bindex->byte += ((v->byte) * looked_up->reset_count) + looked_up->byte_offset;
    bindex->bit = looked_up->new_bit;
}

void itr_lookup(b_i* bindex) {
    if (bindex->bit == 7) {
        bindex->bit = 0;
        bindex->byte += 1;
    }
    else {
        bindex->bit += 1;
    }
}

void detr_lookup(b_i* bindex) {
    if (bindex->bit == 0) {
        bindex->bit = 7;
        bindex->byte -= 1;
    }
    else {
        bindex->bit -= 1;
    }
}

void buildLookup() {
    for(short bit = 0;bit<8;bit++) {
        // lookup[bit][0].byte_offset = 0;
        // lookup[bit][0].new_bit = bit;
        // lookup[bit][0].reset_count = 1;
        for(long offset = 0;offset<8;offset++) {
            get_add_offset(&lookup[bit][offset],bit,offset);
        }
    }
    // for(short bit = 0;bit<8;bit++) {
    //     printf("%d\n",bit);
    //     for(long offset = 0;offset<8;offset++) {
    //         printf("%ld: byte_offset = %ld, new_bit = %d, reset_count = %ld\n",offset,lookup[bit][offset].byte_offset,lookup[bit][offset].new_bit,lookup[bit][offset].reset_count);
    //     }
    //     printf("\n");
    // }
}

void siv_up(unsigned char* array_map, b_i* start) {
    b_i current = *start;
    add_lookup(&current, start);
    while(current.byte < UPPER_BOUND_ARY) {
        // printf("%ld\n",current.byte*30 + MAGIC_ARRAY[current.bit]);
        array_map[current.byte] = array_map[current.byte] | BITMASK[current.bit];
        add_lookup(&current, start);
    }
}

void calculate_primes() {
    buildLookup();
    unsigned char array_map[UPPER_BOUND_ARY] = {0};
    array_map[0] = array_map[0] + BITMASK[0];
    b_i current = {0, 1};
    while(current.byte < UPPER_BOUND_ARY) {
        if(!(array_map[current.byte] & BITMASK[current.bit])) {
            siv_up(array_map, &current);
            // break;
        }
        itr_lookup(&current);
    }
    while(to_long(&current) > UPPER_BOUND) {
        detr_lookup(&current);
    }
    while((array_map[current.byte] & BITMASK[current.bit])) {
        detr_lookup(&current);
    }
    printf("%ld\n",to_long(&current));
    // for(long i = 0;i<100;i++) {
    //     printf("%d\n",array_map[i]);
    // }
    // for(long i = 0;i<UPPER_BOUND_ARY;i++) {
    //     for(short ii = 0;ii<8;ii++) {
    //         // if(true) {
    //         if(!(array_map[i] & BITMASK[ii])) {
    //             printf("%ld ",i*30 + MAGIC_ARRAY[ii]);
    //         }
    //     }
    // }
    // printf("\n");
    // long i = UPPER_BOUND-1;
    // printf("%ld\n",i);

}

int main(int argc, char *argv[]) {
    // buildLookup();
    for(int i = 0;i<100;i++) {
        calculate_primes();
    }
    // b_i current = {0, 1};
    // b_i add = {0, 1};
    // printf("%ld\n",to_long(&current));
    // printf("%ld\n",to_long(&add));
    // add_lookup(&current,&add);
    // printf("%ld\n",to_long(&current));
    // printf("%d\n",in_magic_i(17));
    // for(int i = 0;i<100;i++) {
    //     calculate_primes();
    // }
}