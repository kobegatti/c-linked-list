#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

//////////////////////////////////////////////////
// Function Prototypes
//////////////////////////////////////////////////
Node* append(Node* head, char* id, int val);

static Node* breakCycle(Node* head);

Node* createNode(char* id, int val);

Node* deleteNode(Node* head, int index);

Node* findMiddle(Node* head);

int freeLinkedList(Node* head); /* returns number of nodes freed */

static int hasCycle(Node* head);

Node* insert(Node* head, int index, char* id, int val);

static Node* merge(Node* left, Node* right);

Node* mergeSort(Node* head);

void printLinkedList(Node* head);

Node* reverse(Node* head);

int search(Node* head, char* id);

static void transferNode(Node** from, Node** to);


//////////////////////////////////////////////////
// Function Definitions 
//////////////////////////////////////////////////
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

Node* deleteNode(Node* head, int index)
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
	while (next && i < index - 1)
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

Node* findMiddle(Node* head)
{
	if (!head || !head->next) { return head; }

	Node* slow = head;
	Node* fast = head->next;

	while (fast && fast->next 
		&& fast != head && fast->next != head) // handle cycles
	{
		slow = slow->next;
		fast = fast->next->next;
	}

	return slow;
}



static Node* breakCycle(Node* head)
{
	if (hasCycle(head))
	{
		Node* slow = head, *fast = head->next, *prev = NULL;

		while (slow != fast)
		{
			prev = fast;
			slow = slow->next;
			fast = fast->next->next;
		}

		head = prev->next;
		prev->next = NULL;
	}

	return head;
}

int freeLinkedList(Node* head)
{
	Node* ptr1 = NULL, *ptr2 = NULL;
	int len = 0;

	head = breakCycle(head);

	ptr1 = head;
	ptr2 = head;
	
	while (ptr1)
	{
		ptr2 = ptr1->next;
		free(ptr1);
		ptr1 = ptr2;
		len++;
	}

	head = NULL;
	
	return len;
}

static int hasCycle(Node* head)
{
	Node* slow = head, *fast = head;

	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;

		if (slow == fast) { return 1; }
	}

	return 0;
}

Node* insert(Node* head, int index, char* id, int val)
{
	Node* newNode = NULL, *curr = NULL, *next = NULL;
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
	while (next && i < index - 1)
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

Node* merge(Node* left, Node* right)
{
	Node* merged = NULL;
	Node** tail = &merged;

	while (1)
	{
		if (!left)
		{
			*tail = right;
			break;
		}

		if (!right)
		{
			*tail = left;
			break;
		}

		transferNode(left->val <= right->val ? &left : &right, tail);
		tail = &(*tail)->next;
	}

	return merged;
}

Node* mergeSort(Node* head)
{
	Node* mid, *rightSide, *left, *right = NULL;

	if (!head || !head->next) { return head; }

	mid = findMiddle(head);
	rightSide = mid->next;
	mid->next = NULL;

	left = mergeSort(head);
	right = mergeSort(rightSide);

	return merge(left, right);
}

void printLinkedList(Node* head)
{
	Node* ptr = head;
	int i = 0;
	
	while (ptr)
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

	while (curr)
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

	while (ptr)
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

void transferNode(Node** from, Node** to)
{
	Node* temp = *from;
	*from = (*from)->next;
	temp->next = NULL;
	*to = temp;
}
