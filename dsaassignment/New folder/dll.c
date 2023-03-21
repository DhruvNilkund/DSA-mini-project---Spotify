#include "dll.h"
#include <stdio.h>
#include <stdlib.h>

list_t* create_list()  // return a newly created empty doubly linked list
{
	// DO NOT MODIFY!!!
	list_t* l = (list_t*) malloc(sizeof(list_t));
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
	return l;
}

void insert_front(list_t* list, int data)  // TODO: inserts data to the beginning of the linked list
{
	struct node*temp=(struct node*)malloc(sizeof(struct node));
	temp->data=data;
	temp->next=list->head;
	list->head->prev=temp;
	temp->prev=NULL;
	list->head=temp;
}

void insert_back(list_t* list, int data) // TODO: inserts data to the end of the linked list
{
	struct node *temp=(struct node*)malloc(sizeof(struct node));
	temp->data=data;
	list->tail->next=temp;
	temp->prev=list->tail;
	list->tail=temp;
	temp->next=NULL;
}

void insert_after(list_t* list, int data, int prev) // TODO: inserts data after the node with data “prev”. Do not insert or do anything if prev doesn't exist
{
	struct node*present=list->head;
	struct node*temp=(struct node*)malloc(sizeof(struct node));
	temp->data=data;
	while (present!=NULL && present->data!=prev)
	{
       present=present->next;
	}
	if (present==NULL)
	{\


	
		return;
	}
	else 
	{
		temp->next=present->next;
		present->next=temp;
		temp->prev=present;
	    if (temp->next!=NULL)
		temp->next->prev=temp;
		if (list->tail==present)
		list->tail=temp;
	}
}

void delete_front(list_t* list) // TODO: delete the start node from the linked list.
{
	struct node*present=list->head;
	if (list->head!=NULL){
	list->head=list->head->next;
	free(present);
	if (list->head!=NULL)
	list->head->prev=NULL;
	}
}

void delete_back(list_t* list) // TODO: delete the end node from the linked list.
{
	struct node*present=list->tail;
	if (list->tail!=NULL)
	{
		list->tail=list->tail->prev;
		if (list->tail!=NULL)
		list->tail->next=NULL;
		free(present);
	}
}

void delete_node(list_t* list, int data) // TODO: delete the node with “data” from the linked list.
{
	struct node*present=list->head;
	while (present!=NULL && present->data!=data)
	{
		present=present->next;
	}
	if (present==NULL)
	return;
	else
	{
		if (present->prev!=NULL)
		{
			present->prev->next=present->next;
		}
		else {
			list->head=present->next;
		}
		if (present->next!=NULL)
		{
			present->next->prev=present->prev;
		}
		else{
			list->tail=present->prev;
		}
	}
}

node_t* search(list_t* list, int data) // TODO: returns the pointer to the node with “data” field. Return NULL if not found.
{	
	struct node*present=list->head;
	while (present!=NULL && present->data!=data)
	{
		present=present->next;
	}
	if (present==NULL)
	{
		return NULL;
	}
	else {
		return present;
	}
}

int is_empty(list_t* list) // return true or 1 if the list is empty; else returns false or 0
{
	return list->size == 0;
}

int size(list_t* list) // returns the number of nodes in the linked list.  
{
	// DO NOT MODIFY!!!
	return list->size;
}

void delete_nodes(node_t* head) // helper
{
	// DO NOT MODIFY!!!
	if(head == NULL)
		return;
	delete_nodes(head->next);
	free(head);	
}

void delete_list(list_t* list) // free all the contents of the linked list
{
	// DO NOT MODIFY!!!
	delete_nodes(list->head);
	free(list);
}

void display_list(list_t* list) // print the linked list by separating each item by a space and a new line at the end of the linked list.
{
	// DO NOT MODIFY!!!
	node_t* it = list->head;
	while(it != NULL)
	{
		printf("%d ", it->data);
		it = it->next;
	}
	printf("\n");
}

