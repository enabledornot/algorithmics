#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.c"

typedef struct HuffmanNode {
    int count;
    char c;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
} HNode;

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
    HNode* new_node = (HNode*)(malloc(sizeof(HNode)));
    new_node->count = a->count + b->count;
    new_node->c = NULL;
    new_node->right = a;
    new_node->left = b;
    return new_node;
}

struct Node* buildHuffmanTree(int* counts) {
    for(int i = 0; i < 256; i++) {
        printf("%d ",counts[i]);
    }
    printf("\n");
    LinkedList* LL = create_linked();
    for(int i = 0; i < 256; i++) {
        HNode* new_node = (HNode*)(malloc(sizeof(HNode)));
        new_node->count = counts[i];
        new_node->c = (char)(i);
        new_node->right = NULL;
        new_node->left = NULL;
        insert_sorted(LL, new_node);
    }
    Iter* itr = create_iter(LL);
    HNode* current_node = iter_get(itr);
    // printf("%p\n",current_node);
    while(current_node != NULL) {
        printf("%d\n",current_node->count);
        iter_next(itr);
        current_node = iter_get(itr);
    }
    // free(itr);

    iter_goto_front(itr);
    while(LL->size != 1) {
        HNode* a = iter_remove(itr);
        HNode* b = iter_remove(itr);
        HNode* new = HNode_join(a,b);
        insert_sorted(LL,new);
    }
    return iter_get(itr);
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
    printf("\n");
    buildHuffmanTree(counts);
    fclose(file);
    return 0;
}