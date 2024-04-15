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
        int c_id = current_node->c;
        printf("[%d] %c  -%d\n",c_id,current_node->c,current_node->count);
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
        int c_id = (int)root_node->c;
        charLookup[c_id] = current_lookup;
    }
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
        current_node = current_node->right;
        // break;
    }
    file = fopen(argv[1],"r");
    CR charLookup[257];
    for(int i = 0; i<257; i++) {
        charLookup[i] = (CR){-1,0};
    }
    buildHuffmanLookup(charLookup, root_node, (CR){0,0});
    for(int i = 0; i<257; i++) {
        printf("[%d] %c - %d - %d\n",i,(char)i,charLookup[i].length,charLookup[i].data);
    }
    return 0;
}