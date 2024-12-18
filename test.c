#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "node.h"

/* Function Prototypes */
void testCreateNode(int val, char* s);

void testAppend(Node* head, char* s, int val, int expectedLen);

void testFreeLinkedList(Node* head, int expectedLen);

void testInsert(Node* head, int idx, char* s, int val); 

void testDelete(Node* head, int index, int expectedLen);

void testSearch(Node* head, char* id, int expectedIdx);

void testReverse(Node* head, Node* expected);

int main(void)
{
	testCreateNode(30, "Warriors");

	testAppend(NULL, "Howdy", 5, 1);
	testAppend(append(append(NULL, "Hi", 1), "Hey", 3), "Howdy", 5, 3);

	testFreeLinkedList(NULL, 0);
	testFreeLinkedList(append(NULL, "K&R-C", 0), 1);
	testFreeLinkedList(append(append(NULL, "K&R-C", 0), "Rust", 1), 2);

	testInsert(NULL, 0, "Mario", 1);
	testInsert(NULL, 5, "Luigi", 2); // Index out of range
	testInsert(append(NULL, "Mario", 1), 1, "Luigi", 2);
	testInsert(append(NULL, "Mario", 1), 2, "Luigi", 2); // Index out of range
	testInsert(append(NULL, "Mario", 1), -1, "Luigi", 2); // Index out of range
	testInsert(append(append(NULL, "Mario", 1), "Luigi", 2), 1, "Wario", 3);
	testInsert(append(append(append(NULL, "Mario", 1), "Wario", 3), "Luigi", 2), 3, "Waluigi", 4);

	testDelete(NULL, 0, 0);
	testDelete(append(NULL, "ARM", 1), 0, 0);
	testDelete(append(NULL, "ARM", 1), 1, 1); // no delete
	testDelete(append(append(NULL, "RISC-V", 1), "ARM", 2), 0, 1);
	testDelete(append(append(NULL, "RISC-V", 1), "ARM", 2), 1, 1);
	testDelete(append(append(append(NULL, "Intel", 1), "RISC-V", 2), "ARM", 3), 1, 2);

	testSearch(NULL, "Curry", -1);
	testSearch(append(NULL, "Curry", 30), "Curry", 0);
	testSearch(append(append(NULL, "Green", 23), "Curry", 30), "Curry", 1);
	testSearch(append(append(NULL, "Green", 23), "Curry", 30), "Thompson", -1);
	testSearch(append(append(append(NULL, "Hield", 7), "Green", 23), "Curry", 30), "Green", 1);

	testReverse(NULL, NULL);
	testReverse(append(NULL, "Embedded", 1), append(NULL, "Embedded", 1));
	testReverse(append(append(NULL, "C", 2), "Embedded", 1), append(append(NULL, "Embedded", 1), "C", 2));
	testReverse(append(append(append(NULL, "AudioVideo", 3), "C", 2), "Embedded", 1), append(append(append(NULL, "Embedded", 1), "C", 2), "AudioVideo", 3));
}

void testCreateNode(int val, char* s)
{
	Node* node = createNode(s, val);
	assert(node != NULL && "node must not be null");
	assert(strcmp(node->id, s) == 0);
	assert(node->val == val);

	free(node);	
	node = NULL;
	assert(node == NULL && "node should be free");
}

void testAppend(Node* head, char* s, int val, int expectedLen)
{
	Node* ptr = NULL;
	int actualLen = 1;

	head = append(head, s, val);
	
	ptr = head;
	while (ptr->next)
	{
		ptr = ptr->next;
		actualLen++;
	}

	assert(ptr->val == val);
	assert(strcmp(ptr->id, s) == 0);
	assert(actualLen == expectedLen);

	freeLinkedList(head);
}

void testFreeLinkedList(Node* head, int expectedLen)
{
	assert(freeLinkedList(head) == expectedLen);	
}

void testInsert(Node* head, int idx, char* s, int val)
{
	Node* ptr = NULL;
	int i = 0;

	head = insert(head, idx, s, val);
	
	ptr = head;
	while(ptr && i < idx)
	{
		ptr = ptr->next;
	}	

	if (i != idx) { return; }

	assert(i == idx);
	assert(strcmp(ptr->id, s) == 0);
	assert(ptr->val == val);

	freeLinkedList(head);
} 

void testDelete(Node* head, int index, int expectedLen)
{
	Node* ptr = NULL;
	int actualLen = 0;

	head = delete(head, index);

	ptr = head;
	while(ptr)
	{
		ptr = ptr->next;
		actualLen++;
	}

	assert(actualLen == expectedLen);

	freeLinkedList(head);
}

void testSearch(Node* head, char* id, int expectedIdx)
{
	assert(expectedIdx == search(head, id)); 

	freeLinkedList(head);
}

void testReverse(Node* head, Node* expected)
{
	Node* ptr1 = expected;
	Node* ptr2 = NULL;

	head = reverse(head);
	ptr2 = head;

	while(ptr1 && ptr2)
	{
		assert(ptr1->val == ptr2->val);
		assert(strcmp(ptr1->id, ptr2->id) == 0);
		
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
	}
}
