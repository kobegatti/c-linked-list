#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

Node* append(Node* head, int i, char* c)
{
	Node* ptr = head;
	
	if (head == NULL)
	{
		head = createNode(i, c);
		return head;
	}

	while (ptr->next)
	{
		ptr = ptr->next;
	}

	ptr->next = createNode(i, c);

	return head;
}

Node* createNode(int i, char* c)
{
	Node* node = malloc(sizeof(Node));

	node->num = i;
	strcpy(node->str, c);

	return node;
}

void freeLinkedList(Node* head)
{
	Node* ptr1 = head;
	Node* ptr2 = ptr1;
	
	while(ptr1)
	{
		ptr2 = ptr1->next;
		free(ptr1);
		ptr1 = ptr2;
	}

	head = NULL;
}

void printList(Node* head)
{
	Node* ptr = head;
	int i = 0;
	
	while(ptr)
	{
		printf("(%d: val=%d,str=%s)->", i, ptr->num, ptr->str);
		ptr = ptr->next;
		i++;
	}

	printf("||\n");
}
