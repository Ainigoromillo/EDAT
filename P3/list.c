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

    if(temp_node->next != NULL){
        if(order == 1){
            while(f(e, temp_node->next->data) > 1){
                temp_node = temp_node->next;
                if(temp_node == pl->last){
                    break;
                }
            }
        }else if(order == -1){
            while(f(e, temp_node->next->data) < 1){
                temp_node = temp_node->next;
                if(temp_node == pl->last){
                    break;
                }
            }
        }
    }

    if(temp_node == pl->last){
        list_pushBack(pl, e);
    }else{
        newNode->next = temp_node->next;
        temp_node->next = newNode;
    }

    return OK;
}


/**
 * @brief Public function that pops the front element from a List.
 *
 * Extracts the front element from the List, returning a pointer to it.
 *
 * @param pl Pointer to the List.
 *
 * @return Pointer to the extracted element, or NULL in case of error.
 */
void *list_popFront(List *pl);

/**
 * @brief Public function that pops the back element from a List.
 *
 * Extracts the element element from the List, returning a pointer to it.
 *
 * Note that it is necessary to traverse the list in order to obtain the
 * extract position, so this operation is linear in the number of List elements.
 *
 * @param pl Pointer to the List.
 *
 * @return Pointer to the extracted element, NULL if the List is empty or NULL.
 */
void *list_popBack(List *pl);

/**
 * @brief Public function that frees a List.
 *
 * Frees all the memory allocated for the List.
 *
 * @param pl Pointer to the List.
 */
void list_free(List *pl);

/**
 * @brief Public function that returns the number of elements in a List.
 *
 * Note that the number of elements is not stored in the data structure, and the
 * List must be traversed in order to obtain its size. So this operation is linear
 * in the number of List elements.
 *
 * @param pl Pointer to the List.
 *
 * @return Returns the number of elements in the List, or -1 if the List is NULL.
 */
size_t list_size(const List *pl);

/**
 * @brief Public function that prints the content of a List.
 *
 * Prints all the elements in the List, from front to rear, to an output stream.
 *
 * Note that this function simply calls the P_ele_print function for each List
 * element, also printing the size of this list at the beginning and an additional blank space 
 * between elements.
 * Any other desired format must be included in the P_ele_print function.
 *
 * @param fp Output stream.
 * @param pl Pointer to the List.
 * @param f A pointer to the function that must be used to print the list elements.
 *
 * @return The sum of the return values of all the calls to P_ele_print if these
 * values are all positive; the first negative value encountered otherwise. If the
 * function P_ele_print is well constructed, this means that, upon successful return,
 * this function returns the number of characters printed, and a negative value if
 * an error occurs.
 */
int list_print(FILE *fp, const List *pl, P_ele_print f);