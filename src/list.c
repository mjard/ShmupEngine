//
//  list.c
//  ShmupEngine
//

#include "list.h"

list * 
list_new()
{
	list *list = malloc(sizeof(list));
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

void
list_destroy(list *l, int recursive)
{	
	if (recursive) {
		list_node *node = l->head;
		list_node *next = NULL;
		while (node != NULL) {
			next = node->next;
			free(node);
			node = next;
		}
	}
	
	free(l);
}

list_node * 
list_insert(list *list, void *data) 
{
	list_node *node = malloc(sizeof(list_node));
	
	if (node == NULL) {
		fprintf(stderr, "Failed to allocate node\n");
		return NULL;
	}
	
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	
	if (list->tail != NULL) {
		node->prev = list->tail;
		list->tail->next = node;
		list->tail = node;		
	} else {
		list->head = node;
		list->tail = node;
	}
	list->size++;
	return node;
}

void *
list_remove(list *list, list_node *node)
{
	void *data = node->data;
	
	if (list->size == 0) {
		return NULL;
	} else if (list->size == 1) {
		list->head = NULL;
		list->tail = NULL;
	} else if (node == list->head) {
		list->head = node->next;
		node->next->prev = NULL;
	} else if (node == list->tail) {
		list->tail = node->prev;
		node->prev->next = NULL;
	} else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	
	free(node);
	list->size--;
	return data;
	
}