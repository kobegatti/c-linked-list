#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "node.h"

/* Function Prototypes */
void testCreateNode(int i, char* c);

void testAppend(Node* head, int i, char* c, int expectedLen);

int main(void)
{
	testCreateNode(30, "Warriors");
	testAppend(NULL, 5, "Howdy", 1);
	testAppend(append(append(NULL, 1, "Hi"), 3, "Hey"), 5, "Howdy", 3);
}

void testCreateNode(int i, char* s)
{
	Node* node = createNode(i, s);
	assert(node != NULL && "node must not be null");
	assert(strcmp(node->str, s) == 0);
	assert(node->num == i);

	free(node);	
	node = NULL;
	assert(node == NULL && "node should be free");
}

void testAppend(Node* head, int i, char* c, int expectedLen)
{
	Node* ptr = NULL;
	int actualLen = 1;

	head = append(head, i, c);
	
	ptr = head;
	while (ptr->next)
	{
		ptr = ptr->next;
		actualLen++;
	}

	assert(ptr->num == i);
	assert(strcmp(ptr->str, c) == 0);
	assert(actualLen == expectedLen);

	/* printList(head); */
	freeLinkedList(head);
}

void testFreeLinkedList(void)
{
	
}
