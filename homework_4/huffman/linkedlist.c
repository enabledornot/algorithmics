#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node_linked {
    struct Node_linked* next_node;
    struct Node_linked* prev_node;
    void* element;
} Node;
typedef struct LinkedList_s {
    Node* first_node;
    Node* last_node;
    int size;
} LinkedList;
typedef struct Iterator {
    LinkedList* list;
    Node* current_node;
} Iter;

LinkedList* create_linked() {
    LinkedList *new_linked = (LinkedList*)(malloc(sizeof(LinkedList)));
    new_linked->first_node = NULL;
    new_linked->last_node = NULL;
    new_linked->size = 0;
}
Iter* create_iter(LinkedList* list) {
    Iter *new_iter = (Iter*)(malloc(sizeof(Iter)));
    new_iter->list = list;
    new_iter->current_node = list->first_node;
}
void iter_goto_front(Iter* itr) {
    itr->current_node = itr->list->first_node;
}
void iter_goto_back(Iter* itr) {
    itr->current_node = itr->list->last_node;
}
void iter_insert(Iter* itr, void* element) {
    itr->list->size += 1;
    Node *new_node = (Node*)(malloc(sizeof(Node)));
    new_node->element = element;
    if(itr->list->first_node != NULL) {
        Node *current = itr->current_node;
        Node *prev;
        if (current != NULL) {
            prev = current->prev_node;
            current->prev_node = new_node;
        }
        else {
            prev = itr->list->last_node;
            itr->list->last_node = new_node;
        }
        if (prev != NULL) {
            prev->next_node = new_node;
        }
        else {
            itr->list->first_node = new_node;
        }
        new_node->prev_node = prev;
        new_node->next_node = current;
    }
    else {
        itr->list->first_node = new_node;
        itr->list->last_node = new_node;
        new_node->prev_node = NULL;
        new_node->next_node = NULL;
    }
    // itr->current_node = new_node;
}
void* iter_remove(Iter* itr) {
    itr->list->size -= 1;
    if (itr->current_node == NULL) {
        return NULL;
    }
    Node *item = itr->current_node;
    if (item->next_node != NULL) {
        if (item->prev_node != NULL) { // middle
            item->prev_node->next_node = item->next_node;
            item->next_node->prev_node = item->prev_node;
        }
        else { // front
            itr->list->first_node = item->next_node;
            item->next_node->prev_node = NULL;
        }
    }
    else {
        if (item->prev_node != NULL) { // back
            itr->list->last_node = item->prev_node;
            item->prev_node->next_node = NULL;
        }
        else { //front & back
            itr->list->first_node = NULL;
            itr->list->last_node = NULL;
        }
    }
    void* data = item->element;
    itr->current_node = item->next_node;
    free(item);
    return data;
}
bool iter_next(Iter* itr) {
    if (itr->current_node == NULL) {
        return false;
    }
    itr->current_node = itr->current_node->next_node;
    return true;
}
void* iter_get(Iter* itr) {
    // printf("%p\n",itr->current_node);
    if(itr->current_node != NULL) {
        // printf("%p\n",itr->current_node->element);
        return itr->current_node->element;
    }
    else {
        return NULL;
    }
}