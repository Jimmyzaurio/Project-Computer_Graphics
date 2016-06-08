#include "list.h"

void initializeList(LIST *l, int size) {
	if (size > 0) {
		l->logicalLength = 0;
		l->elementSize = size;
		l->head = l->tail = NULL;
	}
}

void prepend(LIST *l, void *element) {
	NODE *n = malloc(sizeof(NODE));
	n->data = malloc(l->elementSize);
	memcpy(n -> data, element, l->elementSize);

	n->next = l->head;
	l->head = n;

	if (!l->tail)
		l->tail = l->head;	
	l->logicalLength++;
}

void append(LIST *l, void *element) {
	NODE *n = NULL;
	n = (NODE*)malloc(sizeof(NODE));
	n->data = malloc(l->elementSize);
	n->next = NULL;

	memcpy(n->data, element, l->elementSize);

	if (l->logicalLength == 0)
		l->head = l->tail = n;
	else {
		l->tail->next = n;
		l->tail = n;
	}
	l->logicalLength++;
}

int sizeList(LIST *l) {
	return l->logicalLength;
}

void* getData(LIST l, int pos) {
	NODE *ptr;
	int i = 1;
	for (ptr = l.head; ptr; ptr = ptr->next, i++)
		if (i == pos)
			break;	
	return ptr->data;	
}
