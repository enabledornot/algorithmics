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
    // printf("call\n");
    Iter* itr = create_iter(LL);
    HNode* current_node = iter_get(itr);
    // printf("%p\n",current_node);
    while(current_node) {
        // printf("%d\n",current_node->count);
        // printf("%p - itr\n",current_node);
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
    printf("joining %c & %c \n",a->c,b->c);
    HNode* new_node = (HNode*)(malloc(sizeof(HNode)));
    new_node->count = a->count + b->count;
    new_node->c = '_';
    new_node->right = a;
    new_node->left = b;
    return new_node;
}

HNode* buildHuffmanTree(int* counts) {
    for(int i = 0; i < 256; i++) {
        printf("%d ",counts[i]);
    }
    printf("\n");
    LinkedList* LL = create_linked();
    HNode* end_node = (HNode*)(malloc(sizeof(HNode)));
    end_node->count = 1;
    end_node->c = 256;
    end_node->left = NULL;
    end_node->right = (HNode*)(1);
    insert_sorted(LL,end_node);
    for(int i = 0; i < 256; i++) {
        if(counts[i]) {
            printf("i = %d\n",i);
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
    // printf("%p\n",current_node);
    while(current_node != NULL) {
        printf("[%d] %c  -%d\n",current_node->c,current_node->c,current_node->count);
        iter_next(itr);
        current_node = iter_get(itr);
    }
    // free(itr);

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
    // printf("called\n");
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

void encodeFile(FILE* file, CR* charLookup) {
    int c;
    int rem_offset = 0;
    int toPrint = 0;
    while ((c = fgetc(file)) != EOF) {
        int rem_length = charLookup[c].length;
        int rem_data = charLookup[c].data;
        // printf("rem_data %x\n",rem_data << (32 - rem_length - rem_offset));
        int potential_shift = 32 - rem_length - rem_offset;
        if (potential_shift >= 0) {
            toPrint = toPrint | rem_data << (32 - rem_length - rem_offset);
        }
        else {
            toPrint = toPrint | rem_data >> -1*(32 - rem_length - rem_offset);
        }
        // printf("%c-%d,%s ",c,32 - rem_length - rem_offset,toBinary(rem_data << (32 - rem_length - rem_offset), 32));
        // continue;
        toPrint = toPrint | rem_data << (32 - rem_length - rem_offset);
        rem_offset += rem_length;
        if(rem_offset >= 32) {
            // printf("%x ",toPrint);
            printf("%s ",toBinary(toPrint,32));
            toPrint = rem_data << (64 - rem_offset);
            // printf("%d ",(64 - rem_offset));
            // toPrint = toPrint << (rem_offset - rem_length);
            // printf("%s ",toBinary(toPrint,32));
            rem_offset = rem_offset - 32;
        }
    }
    printf("%s",toBinary(toPrint,32));
    printf("\n");
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <filename>\n",argv[0]);
    }
    FILE* file = fopen(argv[1],"r");

    if(file == NULL) {
        printf("Error opening file %s\n",argv[1]);
        return 1;
    }
    int counts[256];
    countFrequency(file, counts);
    fclose(file);
    printf("\n");
    HNode* root_node = buildHuffmanTree(counts);
    HNode* current_node = root_node;
    printf("%p\n",current_node);
    printf("the tree\n");
    while (current_node) {
        printf("%d\n",current_node->count);
        current_node = current_node->left;
        // break;
    }
    CR charLookup[257];
    for(int i = 0; i<257; i++) {
        charLookup[i] = (CR){-1,0};
    }
    buildHuffmanLookup(charLookup, root_node, (CR){0,0});
    printf("printing lookup\n");
    for(int i = 0; i<257; i++) {
        if(charLookup[i].length != -1)
        printf("[%d] %c - %d - %s\n",i,(char)i,charLookup[i].length,toBinary(charLookup[i].data,charLookup[i].length));
    }
    file = fopen(argv[1],"r");
    printf("printing encoding\n");
    encodeFile(file,charLookup);
    fclose(file);
    return 0;
}