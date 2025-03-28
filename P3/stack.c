#include "stack.h"
#include <stdlib.h>


#define INIT_CAPACITY 2     /*!<Initial capacity of the stack*/
#define FCT_CAPACITY 2      /*!<The factor of growth of the stack*/
#define EMPTY_STACK_TOP -1  /*!<The top value of an empty stack*/
#define PRINT_ERROR -1      /*!<Return value when print function fails*/

struct _Stack{
    void **data;  /*!<Array of elements*/
    int top;      /*!<Index of the top element in the data array*/
    int capacity; /*!<The max capacity of the stack*/
};

/*Declaration of private functions to run the growth of the stack*/
/**
 * @brief Checks if the stack is full and therefore can't admit more elements
 * 
 * @param s pointer to the stack
 * @return Bool that describes if the stack is full (TRUE) or not (FALSE)
 */
Bool stack_is_full(const Stack *s);

/**
 * @brief increases the capacity of the stack according to the factor FCT_CAPACITY
 * 
 * @param s pointer to the stack
 * @return Status that describes if any errors occurred
 */
Status stack_grow(Stack *s);
/*End of private functions*/


Stack *stack_init(){
    Stack *new_Stack = NULL;

    new_Stack = (Stack *)calloc(1, sizeof(Stack));
    if(!new_Stack) return NULL;
    
    new_Stack->capacity = INIT_CAPACITY;

    new_Stack->data = (void **)calloc(new_Stack->capacity, sizeof(void*));
    
    if(!new_Stack->data){
        stack_free(new_Stack);
        return NULL;
    }
    new_Stack->top =EMPTY_STACK_TOP;
    
    return new_Stack;
}   

void stack_free(Stack *s){
    if(s){
        if(s->data) free(s->data);
        free(s);
    }
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
    if(!s  || !s->data || !e) return ERROR;

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
    if(!s || stack_isEmpty(s) == TRUE) return NULL;
    return s->data[s->top];
}

int stack_print(FILE *fp, const Stack *s, P_stack_ele_print f){
    int sum = 0, i;
    long size = 0;
    
    if(!fp || !s || !f){
        return PRINT_ERROR;
    }

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
    if(!s) return 0;
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

Bool stack_is_full(const Stack *s){
    if(!s || !s->data) return FALSE;

    if(stack_size(s) == s->capacity){
        return TRUE;
    }
    return FALSE;
}

/*End of private functions*/