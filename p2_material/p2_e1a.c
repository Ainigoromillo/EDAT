#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define EXTENSION_LENGTH 4


int float_print(FILE *f, void *num);

int float_print(FILE *f, void *num){
    fprintf(f,"%f", ((float *)num));
}

int main(int argc, char *argv[]){
    char txt_extension[] = ".txt";
    FILE *f;
    float grade, *gradeArray1, *gradeArray2;
    int i, num_elements=0;
    Stack *st1, *st2;

    if(!(st1 = stack_init())){
        return 1;
    }elif(!(st2 = stack_init())){
        return 1;
    }


    if(argc != 3){
        printf("El formato de los argumentos debe ser: ""file1.txt file2.txt """);
        return 1;
    }

    if(!(strcmp(argv[1] + (strlen(argv[1] - EXTENSION_LENGTH)), txt_extension))){
        printf("El formato de los argumentos debe ser: ""file1.txt file2.txt """);
        return 1;
    }

    if(!(strcmp(argv[1] + (strlen(argv[1] - EXTENSION_LENGTH)), txt_extension))){
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
        if(!(stack_push(st1, ((void *)(&gradeArray2[i]))))){
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

    free(gradeArray1);
    free(gradeArray2);
    free(st1);
    free(st2);
}