#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "search_queue.h"
#include "file_utils.h"

#define MAX_LINE_LENGTH 1000
#define EXTENSION_LENGTH 4
#define INPUT_EXTENSION ".txt"
#define OUTPUT_EXTENSION ".out"

int main(int argc, char const *argv[]) {
    FILE *f_in = NULL, *f_out = NULL;
    SearchQueue *q = NULL;
    void *e=NULL;
    char line[MAX_LINE_LENGTH];
  
    if (argc != 3) {
        printf("Usage: %s input_file output_file\n", argv[0]);
        exit(EXIT_FAILURE);
      }

    if ((strcmp(argv[1] + (strlen(argv[1]) - EXTENSION_LENGTH), INPUT_EXTENSION)))
    {
        printf("Input file format must be: ""file%s""", INPUT_EXTENSION);
        return 1;
    }
    if ((strcmp(argv[2] + (strlen(argv[2]) - EXTENSION_LENGTH), OUTPUT_EXTENSION)))
    {
        printf("Output file format must be: ""file%s""", OUTPUT_EXTENSION);
        return 1;
    }

    f_in = fopen(argv[1], "r");
    if (!f_in)
    {
        printf("ERROR EN OPEN DEL FICHERO DE ENTRADA");
        return 1;
    }

    q = search_queue_new(string_print, string_cmp);
    if(!q){
        printf("ERROR CREATING SEARCH QUEUE");
        fclose(f_in);
        return 1;
    }

    while(fgets(line, MAX_LINE_LENGTH, f_in)){
        e = string_copy(line);
        if(search_queue_contains(q, e)) string_free(e);
        search_queue_push(q, e);
    }

    fclose(f_in);

    f_out = fopen(argv[2], "w");
    if(!f_out){
        printf("ERROR EN OPEN DEL FICHERO DE SALIDA");
        return 1;
    }
    
    while(!search_queue_isEmpty(q)){
        e = search_queue_pop(q);
        string_print(f_out, e);
        string_free(e);
        e = NULL;
    }
  
    fclose(f_out);
    search_queue_free(q);
    exit(EXIT_SUCCESS);
  }