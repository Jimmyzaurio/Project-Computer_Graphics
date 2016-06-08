#ifndef __LIST_H
#define __LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE, TRUE} bool;

typedef struct node{
	void *data;
	struct node *next;
}NODE;

typedef struct list{
	int logicalLength;
	int elementSize;
	NODE *head;
	NODE *tail;
}LIST;

void initializeList(LIST*, int);
void prepend(LIST*, void *);
void append(LIST*, void *);
int sizeList(LIST *);
void* getData(LIST l, int pos);

#endif