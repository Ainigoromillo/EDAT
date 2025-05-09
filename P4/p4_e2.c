#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "search_queue.h"
#include "file_utils.h"

#define MAX_LINE_LENGTH 1000
#define EXTENSION_LENGTH 4
#define INPUT_EXTENSION ".txt"
#define OUTPUT_EXTENSION ".out"
#define FCLOSEF_SUCCESS 0
#define FIRST_ARGUMENT 1
#define SECOND_ARGUMENT 2
#define N_TOTAL_ARGUMENTS 3

void free_SQ_with_elements(SearchQueue *q){
    void *e = NULL;
    if(!q){
        return;
    }
    
    while(!search_queue_isEmpty(q)){
        e = search_queue_pop(q);
        if(e){
            string_free(e);
            e = NULL;
        }
    }
    search_queue_free(q);
}

int main(int argc, char const *argv[]) {
    FILE *f_in = NULL, *f_out = NULL;
    SearchQueue *q = NULL;
    void *e=NULL;
    char line[MAX_LINE_LENGTH];
  
    if (argc != N_TOTAL_ARGUMENTS) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return EXIT_FAILURE;
      }

    else if ((strcmp(argv[FIRST_ARGUMENT] + (strlen(argv[FIRST_ARGUMENT]) - EXTENSION_LENGTH), INPUT_EXTENSION)))
    {
        fprintf(stderr, "Input file format must be: ""file%s""", INPUT_EXTENSION);
        return EXIT_FAILURE;
    }
    else if ((strcmp(argv[SECOND_ARGUMENT] + (strlen(argv[SECOND_ARGUMENT]) - EXTENSION_LENGTH), OUTPUT_EXTENSION)))
    {
        fprintf(stderr, "Output file format must be: ""file%s""", OUTPUT_EXTENSION);
        return EXIT_FAILURE;
    }

    f_in = fopen(argv[FIRST_ARGUMENT], "r");
    if (!f_in)
    {
        fprintf(stderr, "ERROR OPENING INPUT FILE");
        return EXIT_FAILURE;
    }

    q = search_queue_new(string_print, string_cmp);
    if(!q){
        fprintf(stderr, "ERROR CREATING SEARCH QUEUE");
        fclose(f_in);
        return EXIT_FAILURE;
    }

    while(fgets(line, MAX_LINE_LENGTH, f_in)){
        if(!search_queue_contains(q, (void *)line)){
            e = string_copy(line);
            search_queue_push(q, e);
        }
    }

    if(fclose(f_in) != FCLOSEF_SUCCESS){
        fprintf(stderr, "ERROR CLOSING INPUT FILE");
        free_SQ_with_elements(q);
        return EXIT_FAILURE;
    }

    f_out = fopen(argv[SECOND_ARGUMENT], "w");
    if(!f_out){
        fprintf(stderr, "ERROR OPENING OUTPUT FILE");
        free_SQ_with_elements(q);
        return EXIT_FAILURE;
    }
    
    while(!search_queue_isEmpty(q)){
        e = search_queue_pop(q);
        string_print(f_out, e);
        string_free(e);
        e = NULL;
    }
  
    if(fclose(f_out) != FCLOSEF_SUCCESS){
        fprintf(stderr, "ERROR CLOSING OUTPUT FILE");
        free_SQ_with_elements(q);
        return EXIT_FAILURE;
    }

    search_queue_free(q);
    return EXIT_SUCCESS;
  }