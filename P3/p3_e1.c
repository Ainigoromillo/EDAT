#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "delivery.h"
#include "vertex.h"


#define EXTENSION_LENGTH 4
#define MAX_LINE_TAM 255
#define MAX_NAME 255



int main(int argc, char *argv[]){
    Delivery *delivery = NULL;
    char txt_extension[] = ".txt", name[MAX_NAME], product_name[MAX_NAME], str[MAX_LINE_TAM];
    FILE *pf = NULL;
    int num, i;
    void *city = NULL;

    if(argc != 2){
        printf("Error con el numero de argumentos: el formato de los argumentos debe ser: ""file.txt""");
        return 1;
    }

    if((strcmp(argv[1] + (strlen(argv[1]) - EXTENSION_LENGTH), txt_extension))){
        printf("El formato de los argumentos debe ser: ""file.txt""");
        return 1;
    }
    pf = fopen(argv[1], "r");
    if(!pf){
        return 1;
    }

    fscanf(pf, "%s",name);
    fscanf(pf, "%s", product_name);
    delivery = delivery_init(name, product_name);
    if(!delivery) return 1;

    fscanf(pf, "%d", &num);
    fgets(str, MAX_CHARS_IN_LINE, pf);
    
    for(i = 0; i < num; i++){
        if(fgets(str, MAX_LINE_TAM, pf) == NULL){
            return 1;
        }
        city = (void *)vertex_initFromString(str);
        delivery_add(stdout, delivery, city, vertex_print);
    }


    delivery_run_plan(stdout, delivery, vertex_print, vertex_free);

    delivery_free(delivery);
    return 0;

}

