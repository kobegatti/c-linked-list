#ifndef NODE_H
#define NODE_H

#include "utils.h"

#define APPEND 1
#define INSERT 2
#define DELETE 3
#define PRINT 4
#define REVERSE 5
#define SEARCH 6
#define SORT 7
#define EXIT 8 

#ifdef DEBUG
	#define INDEX_OUT_OF_RANGE(index) \
			fprintf(stderr, "Error: Index %d is out of range\n", index)
#else
	#define INDEX_OUT_OF_RANGE(index) do {} while (0)
#endif

typedef struct Node 
{
	char id[MAXLINE];
	int val;
	struct Node* next;
} Node;

Node* append(Node* head, char* id, int val);

Node* createNode(char* id, int val);

Node* deleteNode(Node* head, int index);

Node* findMiddle(Node* head);

int freeLinkedList(Node* head); /* returns number of nodes freed */

Node* insert(Node* head, int index, char* id, int val);

Node* mergeSort(Node* head);

void printLinkedList(Node* head);

Node* reverse(Node* head);

int search(Node* head, char* id);

#endif // NODE_H
