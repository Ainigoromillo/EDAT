#ifndef _FILE_UTILS_H
#define _FILE_UTILS_H
#include <stdio.h>
#include "types.h"


/* function type to convert strings to elements of the appropriate type */
/* the functions should allocate memory for the element */
typedef void *(*elem_from_string)(const char *str);

/* generic function type to process an element */
typedef void (*process_element)(const void *element);

/* generic function type to TAD wrappers*/
typedef Status (*tad_insert)(void *tad, const void *elem);
typedef void * (*tad_extract)(void *tad);
typedef Bool (*tad_isEmpty)(const void * tad);

int *int_init(int a);
void *int_copy (const void *a);
int int_cmp (const void *c1, const void *c2); 
void int_free (void *a);
int int_print(FILE *pf, const void *a); 


char *char_init (char a);
void *char_copy (const void *a); 
int char_cmp (const void *c1, const void *c2); 
void char_free (void *a); 
int char_print (FILE *pf, const void *a); 

float *float_init (float a);
void *float_copy (const void *a); 
int float_cmp (const void *c1, const void *c2); 
void float_free (void *a); 
int float_print (FILE *pf, const void *a); 

void *string_copy (const void *src); 
int string_cmp (const void *c1, const void *c2); 
void string_free (void *str); 
int string_print (FILE *pf, const void *str); 


 
void *str2int(const char *str);

void *str2str(const char *str);

void *str2chr(const char *str);



int read_line (FILE *fp, char *buffer);

Status read_tad_from_file (void *tad, char *filename, elem_from_string convert,
        tad_insert f_insert, tad_isEmpty f_isEmpty);


#endif
