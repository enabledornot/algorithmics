#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.c"

typedef struct HuffmanNode {
    int count;
    int c;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
} HNode;

typedef struct CharRecord {
    int length;
    int data;
} CR;

char binaryString[33];

char* toBinary(int input, int len) {
    input = input << 32-len;
    binaryString[32] = '\0';
    for(int i = 0;i<32;i++) {
        if(i == len) {
            binaryString[i] = '\0';
            break;
        }
        if (input < 0) {
            binaryString[i] = '1';
        }
        else {
            binaryString[i] = '0';
        }
        input = input << 1;
    }
    return binaryString;
}

void countFrequency(FILE* file, int* counts) {
    int c;
    for(int i = 0; i < 256; i++) {
        counts[i] = 0;
    }
    while ((c = fgetc(file)) != EOF) {
        counts[c] += 1;
    }
}

void insert_sorted(LinkedList* LL, HNode* new_node) {
    Iter* itr = create_iter(LL);
    HNode* current_node = iter_get(itr);
    while(current_node) {
        if(new_node->count < current_node->count) {
            break;
        }
        iter_next(itr);
        current_node = iter_get(itr);
    }
    iter_insert(itr,(void*)(new_node));
    free(itr);
}

HNode* HNode_join(HNode* a, HNode* b) {
    HNode* new_node = (HNode*)(malloc(sizeof(HNode)));
    new_node->count = a->count + b->count;
    new_node->c = '_';
    new_node->right = a;
    new_node->left = b;
    return new_node;
}

HNode* buildHuffmanTree(int* counts) {
    LinkedList* LL = create_linked();
    HNode* end_node = (HNode*)(malloc(sizeof(HNode)));
    end_node->count = 1;
    end_node->c = 256;
    end_node->left = NULL;
    end_node->right = (HNode*)(1);
    insert_sorted(LL,end_node);
    for(int i = 0; i < 256; i++) {
        if(counts[i]) {
            HNode* new_node = (HNode*)(malloc(sizeof(HNode)));
            new_node->count = counts[i];
            new_node->c = i;
            new_node->right = NULL;
            new_node->left = NULL;
            insert_sorted(LL, new_node);
        }
    }
    Iter* itr = create_iter(LL);
    HNode* current_node = iter_get(itr);
    while(current_node != NULL) {
        iter_next(itr);
        current_node = iter_get(itr);
    }

    while(LL->size != 1) {
        iter_goto_front(itr);
        HNode* a = iter_remove(itr);
        HNode* b = iter_remove(itr);
        HNode* new = HNode_join(a,b);
        insert_sorted(LL,new);
    }
    iter_goto_front(itr);
    HNode* root = iter_get(itr);
    free(itr);
    return root;
}

void buildHuffmanLookup(CR* charLookup, HNode* root_node, CR current_lookup) {
    if(root_node->left) {
        CR new_lookup = {current_lookup.length+1,current_lookup.data << 1};
        buildHuffmanLookup(charLookup,root_node->left,new_lookup);
        new_lookup.data += 1;
        buildHuffmanLookup(charLookup,root_node->right,new_lookup);
    }
    else {
        charLookup[root_node->c] = current_lookup;
    }
}

int rem_offset = 0;
int toPrint = 0;
void encodeBytes(CR code) {
    int potential_shift = 32 - code.length - rem_offset;
    if (potential_shift >= 0) {
        toPrint = toPrint | code.data << (32 - code.length - rem_offset);
    }
    else {
        toPrint = toPrint | code.data >> -1*(32 - code.length - rem_offset);
    }
    rem_offset += code.length;
    if(rem_offset >= 32) {
        fwrite(&toPrint, 1, 4, stdout);
        toPrint = 0;
        int shifted = code.data << (64 - rem_offset);
        // Bitshifts are not completed if they are equal to 32
        // This condition is added to account for that case
        if(rem_offset != 32) {
            toPrint = toPrint | shifted;
        }
        rem_offset = rem_offset - 32;
    }
}

void encodeFile(FILE* file, CR* charLookup) {
    int c;
    while ((c = fgetc(file)) != EOF) {
        encodeBytes(charLookup[c]);
    }
    encodeBytes(charLookup[256]);
    fwrite(&toPrint, 1, 4, stdout);
}

void decodeFile(HNode* root_node) {
    HNode* current_node = root_node;
    int buff = 0;
    while(fread(&buff,4,1,stdin) == 1) {
        for(int i = 0;i<32;i++) {
            if (buff >= 0) {
                current_node = current_node->left;
            }
            else {
                current_node = current_node->right;
            }
            if (!(current_node->left)) {
                if(current_node->c == 256) {
                    break;
                }
                fwrite(&current_node->c, 1, 1, stdout);
                current_node = root_node;
            }
            buff = buff << 1;
        }
    }
}

int encodeEverything(char* file_name) {
    FILE* file = fopen(file_name,"r");

    if(file == NULL) {
        printf("Error opening file %s\n",file_name);
        return 1;
    }
    int counts[256];
    countFrequency(file, counts);
    fwrite(counts, 4, 256, stdout);
    fclose(file);
    HNode* root_node = buildHuffmanTree(counts);
    HNode* current_node = root_node;
    CR charLookup[257];
    for(int i = 0; i<257; i++) {
        charLookup[i] = (CR){-1,0};
    }
    buildHuffmanLookup(charLookup, root_node, (CR){0,0});
    file = fopen(file_name,"r");
    encodeFile(file,charLookup);
    fclose(file);
}

int decodeEverything() {
    int counts[256];
    fread(counts, 4, 256, stdin);
    HNode* root_node = buildHuffmanTree(counts);
    decodeFile(root_node);
}

int main(int argc, char *argv[]) {
    if(argc == 2) {
        return encodeEverything(argv[1]);
    }
    else {
        return decodeEverything();
    }
}