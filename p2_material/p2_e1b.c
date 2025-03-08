#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "vertex.h"
#include <string.h>
#define EXTENSION_LENGTH 4
#define MAX_LINE 100


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
 * @brief prints an element of type float
 * 
 * @param f file for the output
 * @param num float element to be printed
 * @return 1 if an error occurrs and 0 if the function runs succesfully
 */
int float_print(FILE *f,const void *num);

/**
 * @brief frees the stacks and the elements inside them
 * 
 * @param st1 stack 1
 * @param st2 stack 2
 * @param sout output stack
 */
void free_all(Stack *st1, Stack *st2, Stack *sout);



Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout, P_stack_ele_cmp f){
    void *e = NULL;
    Stack *st = NULL;
    if(!sin1 || !sin2 || !sout || !f){
        return ERROR;
    }
    while(stack_isEmpty(sin1) == FALSE && stack_isEmpty(sin2) == FALSE){
        if(f(stack_top(sin1),stack_top(sin2)) > 0){
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


int float_print(FILE *f,const void *num){
    if(!f || !num){
        return 1;
    }
    fprintf(f,"%f", *((float *)num));
    return 0;
}

void free_all(Stack *st1, Stack *st2, Stack *sout){
    int i, size_st1 = stack_size(st1), size_st2 = stack_size(st2), size_sout = stack_size(sout);
    if(st1){
        for(i=0;i<size_st1;i++){
            vertex_free((Vertex*)stack_pop(st1));
        }
        stack_free(st1);
    }
    if(st2){
        for(i=0;i<size_st2;i++){
            vertex_free((Vertex*)stack_pop(st2));
        }
        stack_free(st2);
    }
    if(sout){
        for(i=0;i<size_sout;i++){
            vertex_free((Vertex*)stack_pop(sout));
        }
        stack_free(sout);
    }
}



int main(int argc, char *argv[]){
    char txt_extension[] = ".txt", vertexDescription[MAX_LINE];
    FILE *f;
    int i, num_elements=0;
    Stack *st1, *st2, *sout = NULL;


    /*Control de errores inicial*/
    if(!(st1 = stack_init())){
        return 1;
    }else if(!(st2 = stack_init())){
        free_all(st1, st2, sout);
        return 1;
    }

    if(argc != 3){
        printf("Error con el numero de argumentos: el formato de los argumentos debe ser: ""file1.txt file2.txt """);
        return 1;
    }

    if((strcmp(argv[1] + (strlen(argv[1]) - EXTENSION_LENGTH), txt_extension))){
        printf("El formato de los argumentos debe ser: ""file1.txt file2.txt """);
        return 1;
    }

    if((strcmp(argv[2] + (strlen(argv[2]) - EXTENSION_LENGTH), txt_extension))){
        printf("El formato de los argumentos debe ser: ""file1.txt file2.txt """);
        return 1;
    }




    if(!(f = fopen(argv[1], "r"))){
        printf("Error leyendo el archivo %s", argv[1]);
        return 1;
    }
    fscanf(f, "%d\n", &num_elements);

    if(!num_elements){
        printf("File ""%s"" is empty;", argv[1]);
        return 1;
    }

    for(i=0;i<num_elements;i++){
        fgets(vertexDescription, MAX_LINE, f);
        if(!(stack_push(st1, ((void *)(vertex_initFromString(vertexDescription)))))){
            free_all(st1, st2, sout);
            printf("Error pushing element to st1");
        }
    }
    fclose(f);

    if(!(f = fopen(argv[2], "r"))){
        printf("Error leyendo el archivo %s", argv[2]);
        return 1;
    }
    fscanf(f, "%d\n", &num_elements);

    if(!num_elements){
        printf("File ""%s"" is empty;", argv[2]);
        return 1;
    }

    for(i=0;i<num_elements;i++){
        fgets(vertexDescription, MAX_LINE, f);
        if(!(stack_push(st2, ((void *)(vertex_initFromString(vertexDescription)))))){
            free_all(st1, st2, sout);
            printf("Error pushing element to st2");
        }
    }
    fclose(f);

    printf("Stack 1:\n");
    stack_print(stdout, st1, vertex_print);
    printf("Stack 2:\n");
    stack_print(stdout, st2, vertex_print);

    if(!(sout = stack_init())){
        free_all(st1, st2, sout);
        return 1;
    }
    if(mergeStacks(st1,st2, sout, vertex_cmp) == ERROR){
        free_all(st1, st2, sout);
        return 1;
    }
    printf("\nJoint Ranking: \n");
    stack_print(stdout,sout,vertex_print);
    free_all(st1, st2, sout);
}