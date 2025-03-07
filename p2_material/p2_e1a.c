#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "vertex.h"

/**
 * @brief: Merges two stacks
 *
 * @param sin1, first input stack
 * @param sin2, second input stack
 * @param sout, result stack
 * @return The function returns OK or ERROR
**/
Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout, P_stack_ele_cmp f);
/**
 * @brief Compares two numbers (float *) and returns a negative number if a < b, positive if a > b and 0 if a == b
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int float_cmp(const void *a, const void *b);
/**
 * @brief Compares two vertex and returns a negative number if a(id) < b(id), positive if a(id) > b(id) and 0 if a(id) == b(id)
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int vertex_cmp(const void *a, const void *b);
Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout, P_stack_ele_cmp f){
    void *e = NULL;
    Stack *st = NULL;
    if(!sin1 || !sin2 || !sout){
        return ERROR;
    }
    while(stack_isEmpty(sin1) == FALSE && stack_isEmpty(sin2)){
        if(f(stack_top(sin1),stack_top(sin2) > 0)){
            e = stack_pop(sin1);
        }else{
            e = stack_pop(sin2);
        }
        if(stack_push(sout, e) == ERROR){
            return ERROR;
        }
    }
    if(stack_isEmpty(sin1) == TRUE){
        st = sin2;
    }
    if(stack_isEmpty(sin2) == TRUE){
        st = sin1;
    }
    while(stack_isEmpty(st) == FALSE){
        e = stack_pop(st);
        if(stack_push(sout, e) == ERROR){
            return ERROR;
        }
    }
    return OK;
    
}

int float_cmp(const void *a, const void *b){
    if(*(float *)a > *(float *)b){
        return 1;
    }
    if(*(float *)a < *(float *)b){
        return -1;
    }
    return 0;
}

int Vertex_cmp(const void *a, const void *b){
    Vertex *vertex1 = NULL, *vertex2 = NULL;
    long id1, id2;
    vertex1 = (Vertex *)a;
    vertex2 = (Vertex *)b;
    id1 = vertex_getId(vertex1);
    id2 = vertex_getId(vertex2);
    if(id1 > id2){
        return 1;
    }
    if(id1 < id1){
        return -1;
    }
    return 0;

    
}