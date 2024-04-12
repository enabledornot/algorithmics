#include <stdbool.h>
#include <stdlib.h>

typedef struct Node_linked {
    struct Node_linked* next_node;
    struct Node_linked* prev_node;
    void* element;
} Node;
typedef struct LinkedList_s {
    Node* first_node;
    Node* last_node;
} LinkedList;
typedef struct Iterator {
    LinkedList* list;
    Node* current_node;
} Iter;

LinkedList* create_linked() {
    LinkedList *new_linked = (LinkedList*)(malloc(sizeof(LinkedList)));
    new_linked->first_node = NULL;
    new_linked->last_node = NULL;
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
    Node *new_node = (Node*)(malloc(sizeof(Node)));
    new_node->element = element;
    if(itr->current_node != NULL) {
        Node *current = itr->current_node;
        Node *prev = current->prev_node;
        if(prev != NULL) {
            prev->next_node = new_node;
            new_node->prev_node = prev;
        }
        else {
            new_node->prev_node = NULL;
        }
        current->prev_node = new_node;
        new_node->next_node = current;
    }
    else {
        itr->list->first_node = new_node;
        itr->list->last_node = new_node;
        new_node->prev_node = NULL;
    }
    itr->current_node = new_node;
}
void* iter_remove(Iter* itr) {
    Node* prev_node = itr->current_node->prev_node;
    Node* next_node = itr->current_node->next_node;
    if(prev_node != NULL) {
        prev_node->next_node = next_node;
    }
    if(next_node != NULL) {
        next_node->prev_node = prev_node;
    }
    void* data = itr->current_node->element;
    free(itr);
    itr->current_node = next_node;
    return data;
}
bool iter_next(Iter* itr) {
    if (itr->current_node == NULL) {
        return false;
    }
    if (itr->current_node->next_node == NULL) {
        itr->current_node = itr->current_node->next_node;
        return true;
    }
}
void* iter_get(Iter* itr) {
    if(itr->current_node) {
        return itr->current_node->element;
    }
    else {
        return NULL;
    }
}