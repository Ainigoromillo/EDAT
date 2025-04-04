#include "list.h"

typedef struct _NodeList{
    void *data;
    struct _NodeList *next;
}NodeList;

struct _List{
    NodeList * last;
};

/**
 * @brief creates a new node for the list
 * 
 * @return pointer to the created node
 */
NodeList *node_create(){
    NodeList *newNode=NULL;

    newNode = (NodeList *)calloc(1, sizeof(NodeList));
    if(!newNode){
        return NULL;
    }

    newNode->next = NULL;
    newNode->data = NULL;

    return newNode;
}


List *list_new(){
    List *new_list=NULL;

    new_list = (List *)calloc(1, sizeof(List));
    if(!new_list){
        return NULL;
    }
    new_list->last = NULL;
}

Bool list_isEmpty(const List *pl){
    if(!pl) return FALSE;

    return (pl->last == NULL);
}

Status list_pushFront(List *pl, void *e){
    NodeList *newNode=NULL, *firstNode=NULL, *lastNode=NULL;

    if(!pl || !e){
        return ERROR;
    }

    newNode = node_create();

    if(!newNode){
        return ERROR;
    }

    newNode->data = e;

    if(list_isEmpty(pl)){
        pl->last = newNode;
        newNode->next = NULL;
    }else{
        firstNode = pl->last->next;
        lastNode = pl->last;

        pl->last->next = newNode;
        newNode->next = firstNode;
    }

    return OK;
}


Status list_pushBack(List *pl, void *e){
    NodeList *newNode=NULL, *firstNode=NULL, *lastNode=NULL;

    if(!pl || !e){
        return ERROR;
    }

    newNode = node_create();

    if(!newNode){
        return ERROR;
    }

    if(list_isEmpty(pl)){
        pl->last = newNode;
        newNode->next = NULL;
    }else{
        firstNode = pl->last->next;
        lastNode = pl->last;

        pl->last->next = newNode;
        newNode->next = firstNode;

        pl->last = newNode;
    }

    return OK;
}


Status list_pushInOrder (List *pl, void *e, P_ele_cmp f, int order){
    NodeList *newNode=NULL, *temp_node=NULL;

    if(order < -1 || order > 1 || order == 0 || !f || !e || !pl){
        return ERROR;
    }

    newNode = node_create();
    if(!newNode){
        return ERROR;
    }

    if(list_isEmpty(pl)){
        list_pushBack(pl, e);
        return OK;
    }

    temp_node = pl->last;

    if(temp_node != pl->last){
        if(order == 1){
            while(f(e, temp_node->next->data) > 1){
                if(temp_node->next == pl->last){
                    break;
                }
                temp_node = temp_node->next;
            }
        }else if(order == -1){
            while(f(e, temp_node->next->data) < 1){
                if(temp_node->next == pl->last){
                    break;
                }
                temp_node = temp_node->next;
                
            }
        }
        newNode->next = temp_node->next;
        temp_node->next = newNode;

    }
    else
    {
        list_pushBack(pl, e);
    }

    return OK;
}



void *list_popFront(List *pl){
    NodeList *z=NULL;
    void *e=NULL;

    if(!pl || list_is_empty(pl)) return NULL;

    if(pl->last->next = pl->last){
        e = pl->last->data;
        free(pl->last);
        pl->last=NULL;
        return e;
    }

    z = pl->last->next->next;
    e = pl->last->next->data;
    free(pl->last->next);

    pl->last->next = z;
    return e;
}

void *list_popBack(List *pl){
    NodeList *z=NULL;
    void *e=NULL;

    if(!pl || list_is_empty(pl)) return NULL;

    e = pl->last->data;

    if(pl->last->next = pl->last){
        free(pl->last);
        pl->last=NULL;
        return e;
    }

    z = pl->last;
    while(z->next != pl->last){
        z = z->next;
    }
    z->next = pl->last->next;

    free(pl->last);
    return e;
}


void list_free(List *pl){
    NodeList *pn = NULL;
    if(pl == NULL){
        return;
    }

    while(pl->last != NULL){
        pn = pl->last;
        pl->last = node_get_next(pn);
        node_destroy(pn);
    }

    free(pl);

    return;
}

int list_print(FILE *fp, const List *pl, P_ele_print f){
    NodeList *pn = NULL;
    int count=0;

    if (f == NULL || pl == NULL || fp == NULL){
        return -1;
    }

    pn = pl->last;

    while(pn->next != NULL){
        f(stdout, pn->data);
        pn = pn->next;
        count++;
    }

    return count;
}