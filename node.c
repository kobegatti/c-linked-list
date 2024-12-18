#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

Node* append(Node* head, char* id, int val)
{
	Node* ptr = head;
	
	if (head == NULL)
	{
		head = createNode(id, val);
		return head;
	}

	while (ptr->next)
	{
		ptr = ptr->next;
	}

	ptr->next = createNode(id, val);

	return head;
}

Node* createNode(char* id, int val)
{
	Node* node = malloc(sizeof(Node));

	strcpy(node->id, id);
	node->val = val;

	return node;
}

Node* delete(Node* head, int index)
{
	Node* curr = NULL;
	Node* next = NULL;
	int i = 0;

	if (head == NULL) { return head; }

	if (index == 0)
	{
		curr = head;
		head = curr->next;
		free(curr);
		curr = NULL;
		return head;
	}

	curr = head;
	next = curr->next;
	while(next && i < index - 1)
	{
		curr = next;
		next = next->next;
		i++;
	}

	if (next && i == index - 1)
	{
		curr->next = next->next;
		free(next);
		next = NULL;
	}
	else
	{
		INDEX_OUT_OF_RANGE(index);
	}

	return head;
}

int freeLinkedList(Node* head)
{
	Node* ptr1 = head;
	Node* ptr2 = ptr1;
	int len = 0;
	
	while(ptr1)
	{
		ptr2 = ptr1->next;
		free(ptr1);
		ptr1 = ptr2;
		len++;
	}

	head = NULL;
	
	return len;
}

Node* insert(Node* head, int index, char* id, int val)
{
	Node* newNode = NULL;
	Node* curr = NULL;
	Node* next = NULL;
	int i = 0;

	if (index < 0 || (head == NULL && index > 0))
	{
		INDEX_OUT_OF_RANGE(index);
		return head;
	}

	if (index == 0)
	{
		newNode = createNode(id, val);
		newNode->next = head;
		head = newNode;
		return head;
	}

	curr = head;
	next = curr->next;
	while(next && i < index - 1)
	{
		curr = next;
		next = next->next;
		i++;
	}

	if (i == index - 1)
	{
		newNode = createNode(id, val);
		curr->next = newNode;
		newNode->next = next;
	}
	else
	{
		INDEX_OUT_OF_RANGE(index);
	}

	return head;
}

void printLinkedList(Node* head)
{
	Node* ptr = head;
	int i = 0;
	
	while(ptr)
	{
		printf("(%d: id=%s,val=%d)->", i, ptr->id, ptr->val);
		ptr = ptr->next;
		i++;
	}

	printf("|||\n");
}

Node* reverse(Node* head)
{
	Node* curr = head;
	Node* end = NULL;

	while(curr)
	{
		head = curr;
		curr = curr->next;
		head->next = end;
		end = head;
	}

	return head;
}

int search(Node* head, char* id)
{
	Node* ptr = head;
	int idx = 0;

	while(ptr)
	{
		if (strcmp(ptr->id, id) == 0)
		{
			return idx;
		}

		ptr = ptr->next;
		idx++;
	}

	return -1;
}
