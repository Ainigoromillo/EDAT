#include "list.h"
#include <stdlib.h>

typedef struct _NodeList{
    void *data;
    struct _NodeList *next;
}NodeList;

struct _List{
    NodeList * last;
};

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
    return new_list;
}

Bool list_isEmpty(const List *pl){
    if(!pl) return FALSE;

    return (pl->last == NULL);
}

Status list_pushFront(List *pl, void *e){
    NodeList *newNode=NULL, *firstNode=NULL;

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
        newNode->next = newNode;
    }else{
        firstNode = pl->last->next;

        pl->last->next = newNode;
        newNode->next = firstNode;
    }

    return OK;
}


Status list_pushBack(List *pl, void *e){
    NodeList *newNode=NULL, *firstNode=NULL;

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
        newNode->next = newNode;
    }else{
        firstNode = pl->last->next;

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

    /*Si la lista está vacía, llamamos a push front*/
    if(list_isEmpty(pl)){
        return list_pushFront(pl, e);
    }

    /*Creamos un nuevo nodo para insertarlo manualmente en la lista*/
    newNode = node_create();
    if(!newNode){
        return ERROR;
    }
    newNode->data = e;

    /*Empezaremos desde la última posición de la lista*/
    temp_node = pl->last;

    /*Verificamos si la lista tiene varios elementos o únicamente uno*/
    if(temp_node->next != pl->last){
        /*Si ordenamos de menor a mayor, vamos recorriendo la lista hasta llegar al final o hasta encontrar un elemento mayor que el actual*/
        if(order == 1){
            while(f(e, temp_node->next->data) > 0 && temp_node->next != pl->last){
                temp_node = temp_node->next;
            }
        }else if(order == -1){
            while(f(e, temp_node->next->data) < 0 && temp_node->next != pl->last){
                temp_node = temp_node->next;
            }
        }
        newNode->next = temp_node->next;
        temp_node->next = newNode;
        
    }
    else
    {
        /*Si la lista solo tiene un elemento, lo añadimos directamente*/
        /*1->menor a mayor
        -1->mayor a menor
          */
        newNode->next = pl->last;
        pl->last->next = newNode;
        if(order == 1){
            if(f(e, pl->last->data) > 0){
                pl->last = newNode;
            }
        }else if(order == -1){
            if(f(e, pl->last->data) < 0){
                pl->last = newNode;
            }
        }
    }

    return OK;
}



void *list_popFront(List *pl){
    NodeList *z=NULL;
    void *e=NULL;

    if(!pl || list_isEmpty(pl)) return NULL;

    if(pl->last->next == pl->last){
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

    if(!pl || list_isEmpty(pl)) return NULL;

    e = pl->last->data;

    if(pl->last->next == pl->last){
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
    pl->last = z;
    return e;
}


void list_free(List *pl){
    NodeList *current = NULL, *nextNode = NULL;

    if(pl == NULL || pl->last == NULL){
        free(pl);
        return;
    }

    current = pl->last->next; 
    while (current != pl->last) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    free(pl->last);
    free(pl);

    return;
}

int list_print(FILE *fp, const List *pl, P_ele_print f){
    NodeList *pn = NULL;
    int count=0, i = 1;

    if (f == NULL || pl == NULL || fp == NULL){
        return -1;
    }

    if(list_isEmpty(pl)){
        return 0;
    }

    pn = pl->last;

    while(pn->next != pl->last){
        pn = pn->next;
        count += f(stdout, pn->data);
        i++;
    }
    count += f(stdout, pl->last->data);


    return count;
}

size_t list_size(const List *l){
    NodeList *z=NULL;
    int count=0;

    if(!l) return -1;
    if(list_isEmpty(l)) return 0;

    z = l->last;
    while(z->next != l->last){
        z = z->next;
        count++;
    }
    count ++;
    return count;
}
