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
    iter_insert(itr,(void*)18);
    iter_goto_front(itr);
    iter_next(itr);
    iter_remove(itr);
    iter_next(itr);
    iter_insert(itr,(void*)100);
    iter_next(itr);
    // printf()
    printf("itr get %p\n",iter_get(itr));
    // printf("itr next %d\n",iter_next(itr));
    // printf("itr get %p\n",iter_get(itr));
    // printf("itr next %d\n",iter_next(itr));
    // printf("itr get %p\n",iter_get(itr));
    // printf("itr next %d\n",iter_next(itr));
    // printf("itr get %p\n",iter_get(itr));
    free(itr);
    itr = create_iter(LL);
    void* num = iter_get(itr);
    printf("\nbegin loop\n");
    while(num) {
        num = iter_get(itr);
        bool cond = iter_next(itr);
        printf("status - %d\n",cond);
        printf("%p\n",num);
        // break;
    }
    // printf("%d\n",(int)num);
}