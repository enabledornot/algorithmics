#include "linkedlist.c"
#include <stdio.h>

int main(int argc, char *argv[]) {
    LinkedList* LL = create_linked();
    Iter* itr = create_iter(LL);
    // void* ptr = (void*)10;
    // printf("%d\n",ptr);
    for(int i = 1;i<10;i++) {
        iter_insert(itr,(void*)i);
    }
    // iter_insert(itr,ptr);
    iter_insert(itr,(void*)15);
    free(itr);
    itr = create_iter(LL);
    void* num = iter_get(itr);
    while(num) {
        bool cond = iter_next(itr);
        printf("status - %d\n",cond);
        num = iter_get(itr);
        printf("%p\n",num);
        break;
    }
    printf("%d\n",(int)num);
}