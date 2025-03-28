#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_QUEUE 100    /*Maximum capacity of the queue plus 1 extra position used for the implementation of the queue (real size of the queue is MAX_QUEUE -1)*/

struct _Queue{
    void *data[MAX_QUEUE];
    void **rear, **front;
};

Queue *queue_new(){
    Queue *q;
    int i;
    if(!(q = (Queue *)calloc(1, sizeof(Queue)))){
        return NULL;
    }
    for(i=0;i<MAX_QUEUE;i++){
        q->data[i] = NULL;
    }
    q->front = q->data;
    q->rear = q->data;
    return q;
}


void queue_free(Queue *pq){
    if(pq){
        free(pq);
    }
    return;
}


Bool queue_isEmpty(const Queue *pq){
    if(!pq) return TRUE;

    return (pq->front == pq->rear);
}

Bool queue_is_full(const Queue *pq){
    if(!pq) return TRUE;

    return (pq->front == (pq->rear - pq->data+ 1)%MAX_QUEUE + pq->data);
}

Status queue_push(Queue *pq, void *e){
    if(!pq || !e){
        return ERROR;
    }
    if(queue_is_full(pq)){
        return ERROR;
    }
    *pq->rear = e;
    pq->rear = (pq->rear - pq->data + 1)%MAX_QUEUE + pq->data;
    return OK;
}

void *queue_pop(Queue *pq){
    void *e=NULL;
    if(!pq){
        return NULL;
    }
    if(queue_isEmpty(pq)){
        return NULL;
    }
    e = *(pq->front);
    *(pq->front) = NULL;
    pq->front = (pq->front - pq->data +1)%MAX_QUEUE + pq->data;
    return e;
}

void *queue_getFront(const Queue *pq){
    if(!pq || queue_isEmpty(pq)) return NULL;
    return *(pq->front);
}

void *queue_getBack(const Queue *pq) {
    if ((pq == NULL) || (queue_isEmpty(pq) == TRUE)) {
        return NULL;
    }
    return *((pq->rear - pq->data -1 + MAX_QUEUE)%MAX_QUEUE + pq->data);
}

size_t queue_size(const Queue *pq){
    if(!pq) return 0;
    return ((pq->rear - pq->front + MAX_QUEUE)%MAX_QUEUE);
}

int queue_print(FILE *fp, const Queue *q, p_queue_ele_print f){
    int i, size,count=0;

    size = queue_size(q);

    for(i=0;i<size;i++){
        count += f(fp, q->data[i]);
    }

    return count;
}