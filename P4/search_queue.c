#include <stdlib.h>
#include "search_queue.h"
#include "bstree.h"

#define PRINT_ERROR -1

struct _SearchQueue{
    BSTree *data;
};

SearchQueue *search_queue_new(P_ele_print print_ele, P_ele_cmp cmp_ele){
    BSTree *new_tree=NULL;
    SearchQueue *new_search_queue=NULL;
    
    if(!print_ele || !cmp_ele) return ERROR;

    if(!(new_tree = tree_init(print_ele, cmp_ele))){
        return NULL;
    }

    if(!(new_search_queue = (SearchQueue*)calloc(1, sizeof(SearchQueue)))){
        tree_destroy(new_tree);
        return NULL;
    }

    new_search_queue->data = new_tree;
    return new_search_queue;
}

void search_queue_free(SearchQueue *q){
    if(q){
        if(q->data){
            tree_destroy(q->data);
        }
        free(q);
    }
    return;
}

Bool search_queue_isEmpty(const SearchQueue *q){
    return tree_isEmpty(q->data);
}

Status search_queue_push(SearchQueue *q, void *ele){
    if(!q || !q->data || !ele) return ERROR;
    return tree_insert(q->data, ele);
}

void *search_queue_pop(SearchQueue *q){
    void *e=NULL;
    if(!q || !q->data) return NULL;

    e = tree_find_min(q->data);

    if(!e || !(tree_remove(q->data, e))){
        return NULL;
    }
    return e;
}

void *search_queue_getFront(const SearchQueue *q){
    void *e=NULL;
    if(!q || !q->data) return NULL;

    e = tree_find_min(q->data);

    return e;
}

void *search_queue_getBack(const SearchQueue *q){
    void *e=NULL;
    if(!q || !q->data) return NULL;

    e = tree_find_max(q->data);

    return e;
}

size_t search_queue_size(const SearchQueue *q){
    return tree_size(q->data);
}

int search_queue_print(FILE *fp, const SearchQueue *q){
    if(!fp || !q) return PRINT_ERROR;

    return tree_preOrder(fp, q->data);
}