#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "types.h"
#include "list.h"
#include "file_utils.h"

int main(int argc, char *argv[]){
    char txt_extension[] = ".txt", line[MAX_LINE_TAM];
    FILE *pf = NULL;
    int cmp_arg, num, i ;
    float *notes_array = NULL, *note = NULL;
    List *list_1 = NULL, *list_2 = NULL;

    if(argc < 3){
        printf("Error, se ha insertado muy pocos elementos, Format : ""exectutable filename int_1"".");
        return 1;
    }

    if ((strcmp(argv[1] + (strlen(argv[1]) - EXTENSION_LENGTH), txt_extension)))
    {
        printf("El formato del file debe ser: ""file.txt""");
        return 1;
    }
    pf = fopen(argv[1], "r");
    if (!pf)
    {
        printf("ERROR EN OPEN DEL FICHERO DE LECTURA");
        return 1;
    }
    cmp_arg = atoi(argv[2]);
    if(cmp_arg != -1 && cmp_arg != 1){
        printf("ERROR, el argumento debe ser 1 o -1");
        fclose(pf);
        return 1;
    }

    list_1 = list_new();
    if(!list_1)
    {
        printf("error en la creacion de la lista 1");
        fclose(pf);
        return 1;
    }
    list_2 = list_new();
    if(!list_2)
    {
        printf("error en la creacion de la lista 2");
        fclose(pf);
        list_free(list_1);
        return 1;
    }

    fscanf(pf, "%d", &num);
    notes_array = (float *)malloc(sizeof(float) * num);
    for(i = 0 ; i < num ; i++){
        fscanf(pf, "%lf", &notes_array[i]);
    }

    fclose(pf);

    printf("SIZE : %ld\n", list_size(list_1));
    for(i = 0; i < num ; i++){
        if((i + 1)%2 == 1){ /*posicion impar*/
            list_pushBack(list_1, &notes_array[i]);
        }
        if((i+1)%2 == 0){ /*posicion par*/
            list_pushFront(list_1, &notes_array[i]);
        } 
    }
    list_print(stdout, list_1, float_print);
    printf("Finished inserting");

    printf("Now we extract from the beginning and insert in order: \n");
    for(i = 0; i < num/2 ; i++){
        note = list_popFront(list_1);
        float_print(stdout, note);
        list_pushInOrder(list_2, note, float_cmp, cmp_arg);
    }
    while(list_isEmpty(list_1) == FALSE){
        note = list_popBack(list_1);
        float_print(stdout, note);
        list_pushInOrder(list_2, note, float_cmp, cmp_arg);
    }
    printf("SIZE : %ld\n", list_size(list_2));
    list_print(stdout, list_2, float_print);

    list_free(list_1);
    list_free(list_2);
    free(notes_array);
    
    return 0;
    



}