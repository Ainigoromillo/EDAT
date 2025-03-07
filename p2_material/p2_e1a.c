#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "vertex.h"
#include <string.h>
#define EXTENSION_LENGTH 4


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

int float_print(FILE *f,const void *num);
Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout, P_stack_ele_cmp f){
    void *e = NULL;
    Stack *st = NULL;
    if(!sin1 || !sin2 || !sout){
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
    if(id1 < id2){
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

int main(int argc, char *argv[]){
    char txt_extension[] = ".txt";
    FILE *f;
    float *gradeArray1, *gradeArray2;
    int i, num_elements=0;
    Stack *st1, *st2, *sout = NULL;

    if(!(st1 = stack_init())){
        return 1;
    }else if(!(st2 = stack_init())){
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
    fscanf(f, "%d", &num_elements);

    if(!num_elements){
        printf("File ""%s"" is empty;", argv[1]);
        return 1;
    }

    if(!(gradeArray1 = (float *)calloc(num_elements, sizeof(float)))){
        return 1;
    }

    for(i=0;i<num_elements;i++){
        fscanf(f,"%f", &(gradeArray1[i]));
        if(!(stack_push(st1, ((void *)(&gradeArray1[i]))))){
            stack_free(st1);
            stack_free(st2);
            printf("Error pushing element to st1");
        }
    }
    fclose(f);

    if(!(f = fopen(argv[2], "r"))){
        printf("Error leyendo el archivo %s", argv[2]);
        return 1;
    }
    fscanf(f, "%d", &num_elements);

    if(!num_elements){
        printf("File ""%s"" is empty;", argv[2]);
        return 1;
    }

    if(!(gradeArray2 = (float *)calloc(num_elements, sizeof(float)))){
        return 1;
    }

    for(i=0;i<num_elements;i++){
        fscanf(f,"%f", &(gradeArray2[i]));
        if(!(stack_push(st2, ((void *)(&gradeArray2[i]))))){
            free(gradeArray1);
            stack_free(st1);
            stack_free(st2);
            printf("Error pushing element to st2");
        }
    }
    fclose(f);

    stack_print(stdout, st1, float_print);
    stack_print(stdout, st2, float_print);

    if(!(sout = stack_init())){
        free(gradeArray1);
        free(gradeArray2);
        free(st1);
        free(st2);
        return 1;
    }
    if(mergeStacks(st1,st2, sout, float_cmp) == ERROR){
        free(gradeArray1);
        free(gradeArray2);
        free(st1);
        free(st2);
        return 1;
    }
    printf("Joint Ranking: \n");
    stack_print(stdout,sout,float_print);
    free(gradeArray1);
    free(gradeArray2);
    free(st1);
    free(st2);
}