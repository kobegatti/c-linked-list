#ifndef NODE_H
#define NODE_H
#define APPEND 1
#define INSERT 2
#define DELETE 3
#define PRINT 4
#define REVERSE 5
#define SEARCH 6
#define EXIT 7

#define MAX_STR_LEN 24

typedef struct Node 
{
	int num;
	char str[MAX_STR_LEN];
	struct Node* next;
} Node;

Node* append(Node* head, int i, char* c);

Node* createNode(int i, char* c);

void freeLinkedList(Node* head);

void printList(Node* head);

#endif
