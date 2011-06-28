//
//  list.h
//  ShmupEngine
//

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct list_node {
	void *data;
	struct list_node *next;
	struct list_node *prev;
} list_node;

typedef struct list {
	int size;
	struct list_node *head;
	struct list_node *tail;
} list;

list * list_new();
void list_destroy(list *l, int recursive);
list_node * list_insert(list *l, void *data);
void * list_remove(list *l, list_node *node);

#endif