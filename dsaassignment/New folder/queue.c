#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

queue_t* create_queue()   // return a newly created empty queue
{
	// DO NOT MODIFY!!!
	queue_t* Q = (queue_t*) malloc(sizeof(queue_t));
	Q->list = create_list();
	Q->front = Q->list->head;
	Q->rear = Q->list->tail;
	Q->size = Q->list->size;
	return Q;
}

void enqueue(queue_t* q, int data) // TODO: insert data at the end of a queue
{
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    temp->data=data;
    if (q->front==NULL)
    {
        q->rear=temp;
        q->front=temp;
        q->list->head=q->front;
        q->list->tail=q->rear;
        temp->prev=NULL;
        temp->next=NULL;
    }
    else{
    q->rear->next=temp;
    temp->prev=q->rear;
    q->rear=temp;
    q->list->head=q->front;
    q->list->tail=q->rear;
    temp->next=NULL;
    }
    q->size++;
    q->list->size++;
}

int dequeue(queue_t* q) 	// TODO: return the data at the front of a queue and remove it. Return -1 if queue is empty
{
    if (q->front==NULL);
    else 
    {
        struct node*present=q->front;
        q->front=q->front->next;
        free(present);
        q->front->prev=NULL;
        q->list->head=q->front;
        q->list->tail=q->rear;
        q->size--;
        q->list->size--;
    }
}

int front(queue_t* q) // TODO: return the data at the front of a queue. Return -1 if queue is empty
{
    if (q->front==NULL)
    return -1;
    else 
    {
        return q->front->data;
    }
}

int empty(queue_t* q) // return if the queue is empty
{
	// DO NOT MODIFY!!!
	return is_empty(q->list);
}

int queue_size(queue_t* q) // returns the number of elements in the queue
{
	// DO NOT MODIFY!!!
	return q->size;
}

void delete_queue(queue_t* q) // empty the contents of the queue
{
	// DO NOT MODIFY!!!
	delete_list(q->list);
	free(q);
}