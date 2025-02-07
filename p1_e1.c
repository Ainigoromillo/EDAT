
#include <stdio.h>
#include "vertex.h"

int main(){
    Vertex *v, *w,*t;
    v = vertex_init();
    w = vertex_init();
    vertex_setId(v,10);
    vertex_setId(w,20);
    vertex_setTag(v,"one");
    vertex_setTag(w,"two");
    vertex_setState(v,WHITE);
    vertex_setState(w,BLACK);
    printf("[%ld %s %d][%ld %s %d]\n",vertex_getId(v),vertex_getTag(v),vertex_getState(v),vertex_getId(w),vertex_getTag(w),vertex_getState(w));
    if(vertex_cmp(v,w) == 0){
        printf("Equals? : Si\n");
    }else{
        printf("Equals? : No\n");
    }
    printf("%s\n",vertex_getTag(w));
    t = vertex_copy(v);
    printf("%ld\n",vertex_getId(t));
    printf("[%ld %s %d][%ld %s %d]\n",vertex_getId(v),vertex_getTag(v),vertex_getState(v),vertex_getId(t),vertex_getTag(t),vertex_getState(t));
    if(vertex_cmp(v,t) == 0){
        printf("Equals? : Si\n");
    }else{
        printf("Equals? : No\n");
    }
    vertex_free(v);
    vertex_free(w);
    vertex_free(t);
    


    return 0;
}