#include "vertex.h"
#include <stdlib.h>
#include <string.h>


/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/
Status vertex_setField (Vertex *v, char *key, char *value);

Status vertex_setField (Vertex *v, char *key, char *value) {
  if (!key || !value) return ERROR;

  if (strcmp(key, "id") == 0) {
    return vertex_setId(v, atol(value));
  } else if (strcmp(key, "tag") == 0) {
    return vertex_setTag(v, value);
  } else if (strcmp(key, "state") == 0) {
    return vertex_setState(v, (Label)atoi(value));
  }

  return ERROR;
}

/*----------------------------------------------------------------------------------------*/
/*
*Definicion de la estructura Vertex declarada en vertex.h
*/
#define TAG_LENGTH 64
 struct _Vertex {
 long id;
 char tag[TAG_LENGTH];
 Label state;
 }; 

Vertex * vertex_init (){
  Vertex *v = NULL;
  v =(Vertex *)calloc(1,sizeof(Vertex));
  if(!(v)) return NULL;
  return v;
}


Vertex *vertex_initFromString(char *descr){
  char buffer[1024];
  char *token;
  char *key;
  char *value;
  char *p;
  Vertex *v;

  /* Check args: */
  if (!descr) return NULL;

  /* Allocate memory for vertex: */
  v = vertex_init();
  if (!v) return NULL;

  /* Read and tokenize description: */
  sprintf(buffer, "%s", descr);
  token = strtok(buffer, " \t\n");
  while (token) {
    p = strchr(token, ':');
    if (!p) continue;

    *p = '\0';
    key = token;
    value = p+1;

    vertex_setField(v, key, value);

    token = strtok(NULL, " \t\n");
  }

  return v;
}
void vertex_free (void * v){
  Vertex *w = (Vertex *)v;
  free(v);
}
long vertex_getId (const Vertex * v){
  long id = v->id;
  if(!v) return -1;
  return id;
}
const char* vertex_getTag (const Vertex * v){
  if (!v) return NULL;
  /*char *tag;
  tag = (char *)calloc(strlen(v->tag)  + 1, sizeof(char));
  if(!(tag)) return NULL;
  tag[strlen(v->tag)] = '\0';
  strcpy(tag,v->tag);*/
  return v->tag;
}
Label vertex_getState (const Vertex * v){
  if (!v) return ERROR_VERTEX;
  Label state;
  state = v->state;
  return state;
}
Status vertex_setId (Vertex * v, const long id){
if(!v){
return ERROR;
}
v->id = id;
return OK;
}



Status vertex_setTag (Vertex * v, const char * tag){
if(!v || !tag){
return ERROR;
}
strcpy(v->tag, tag);
return OK;

}

Status vertex_setState (Vertex * v, const Label state){
if(!v){
return ERROR;
}
v->state = state;
return OK;
}

int vertex_cmp (const void * v1, const void * v2){
if(!v1 || !v2){
return 0;
}
Vertex *w1, *w2;
w1 = (Vertex *)v1;
w2 = (Vertex *)v2;

if(w1->id < w2->id){
return -1;
} else if(w1->id > w2->id){
return 1;
}else{
return strcmp(w1->tag, w1->tag);
}
}


void * vertex_copy (const void * src){
if(!src){
return NULL;
}
Vertex *w1;
w1 = vertex_init();
Vertex *wsrc = (Vertex *)src;
w1->id = wsrc->id;
w1->state = wsrc->state;
strcpy(w1->tag, wsrc->tag);
return (void *)w1;
}
/*
int sum=0, i;
if(!v || !pf){
return -1;
}

Vertex *w = (Vertex *)v;

for(i=0;i<strlen(w->tag);i++){
fprintf(stdout, "%c", w->tag[i]);
sum++;
}

*/
int vertex_print (FILE * pf, const void * v){
int sum = 0;
char id[TAG_LENGTH];
Vertex *w = (Vertex *)v;
if(!v) return -1;
fprintf(pf,"[%ld,%s,%d]",vertex_getId(w),vertex_getTag(w),vertex_getState(w));
sprintf(id,"%ld",w->id);
sum = strlen(id) + strlen(w->tag) + 1;
return sum;
}
