#include "stack.h"
#include <stdlib.h>


#define INIT_CAPACITY 2  /*!<Initial capacity of the stack*/
#define FCT_CAPACITY 2   /*!<The factor of growth of the stack*/

struct _Stack{
    void **data;  /*!<Array of elements*/
    int top;      /*!<Index of the top element in the data array*/
    int capacity; /*!<The max capacity of the stack*/
};

/*Declaration of private functions to run the growth of the stack*/
Bool stack_is_full(Stack *s);
Status stack_grow();
/*End of private functions*/


Stack *stack_init(){
    Stack *new_Stack = NULL;

    new_Stack = (Stack *)malloc(sizeof(Stack));
    if(!new_Stack) return NULL;
    new_Stack->capacity = INIT_CAPACITY;
    new_Stack->data = (void **)malloc(sizeof(void**) * new_Stack->capacity);
    if(!new_Stack){
        stack_free(new_Stack);
        return NULL;
    }
    new_Stack->top =-1;
    
    return new_Stack;
}   

void stack_free(Stack *s){
    if(!s) return;
    if(s->data) free(s->data);
    free(s);
    return;
}
Bool stack_isEmpty(const Stack *s){
    if(!s) return TRUE;
    if(s->top < 0){
        return TRUE;
    }
    return FALSE;
}

Status stack_push(Stack *s, const void *e){
    if(!s  || !s->data) return ERROR;
    
    if(stack_is_full(s) == TRUE){
        if(stack_grow(s) == ERROR) return ERROR;
    }
    s->top++;
    s->data[s->top] = (void *)e;
    return OK;
}

void *stack_pop(Stack *s){
    void *e = NULL;
    if(!s  || !s->data) return NULL;
    if(stack_isEmpty(s)){
        return NULL;
    }
    e = s->data[s->top];
    s->data[s->top] = NULL;
    s->top --;
    return e;
}

void *stack_top(const Stack *s){
    if(!s) return NULL;
    return s->data[s->top];
}

int stack_print(FILE *fp, const Stack *s, P_stack_ele_print f){
    int sum = 0, i;
    long size = 0;
    size = stack_size(s);
    fprintf(fp, "SIZE : %ld\n",size);
    for(i = s->top; i >= 0; i--){
        sum += f(fp, s->data[i]);
        fprintf(fp, "\n");
    }

    return sum;

}

size_t stack_size (const Stack *s){
    long size;
    if(!s) return -1;
    size = (long)s->top;
    size ++;
    return size;
}

/*Implementation of private functions*/

Status stack_grow(Stack *stack){
    int new_size;
    void **new_data = NULL;
  
    if ((stack == NULL) || (stack->data == NULL)) {
      return ERROR;
    }
  
    new_size = stack->capacity * FCT_CAPACITY;
    new_data = realloc(stack->data, sizeof(void *) * new_size);
    if (!new_data) {
      return ERROR;
    }
  
    stack->capacity = new_size;
    stack->data = new_data;
    return OK;
}

Bool stack_is_full(Stack *s){
    if(!s || !s->data) return FALSE;

    if(stack_size(s) == s->capacity){
        return TRUE;
    }
    return FALSE;
}

/*End of private functions*/