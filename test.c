#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "node.h"
#include "randomUtils.h"

#define RAND_STR_LEN 9
#define RAND_INT_MIN 0
#define RAND_INT_MAX RAND_MAX

//////////////////////////////////////////////////
// Function Prototypes
//////////////////////////////////////////////////
void compareLists(Node* head, Node* expected);

Node* generateRandomList(size_t len, int min, int max);

void loadTestSort(size_t len, int min, int max);

void testCreateNode(int val, char* s);

void testAppend(Node* head, char* s, int val, int expectedLen);

void testFreeLinkedList(Node* head, int expectedLen);

void testInsert(Node* head, int idx, char* s, int val); 

void testDelete(Node* head, int index, int expectedLen);

void testSearch(Node* head, char* id, int expectedIdx);

void testReverse(Node* head, Node* expected);

void testFindMiddle(Node* head, Node* expected);

void testMergeSort(Node* head, Node* expected);


//////////////////////////////////////////////////
// Function Definitions 
//////////////////////////////////////////////////
int main(void)
{
	// Test createNode
	testCreateNode(30, "Warriors");

	// Test append
	testAppend(NULL, "Howdy", 5, 1);
	testAppend(append(append(NULL, "Hi", 1), "Hey", 3), "Howdy", 5, 3);

	// Test freeLinkedList
	testFreeLinkedList(NULL, 0);
	testFreeLinkedList(append(NULL, "K&R-C", 0), 1);
	testFreeLinkedList(append(append(NULL, "K&R-C", 0), "Rust", 1), 2);
	Node* fr = append(append(append(NULL, "C", 0), "K&R-C", 1), "Rust", 2);
	Node* p1 = fr;
	while (p1->next) { p1 = p1->next; }
	p1->next = fr; // create cycle
	testFreeLinkedList(fr, 3);

	// Test insert
	testInsert(NULL, 0, "Mario", 1);
	testInsert(NULL, 5, "Luigi", 2); // Index out of range
	testInsert(append(NULL, "Mario", 1), 1, "Luigi", 2);
	testInsert(append(NULL, "Mario", 1), 2, "Luigi", 2); // Index out of range
	testInsert(append(NULL, "Mario", 1), -1, "Luigi", 2); // Index out of range
	testInsert(append(append(NULL, "Mario", 1), "Luigi", 2), 1, "Wario", 3);
	testInsert(append(append(append(NULL, "Mario", 1), "Wario", 3), "Luigi", 2), 3, "Waluigi", 4);

	// Test deleteNode
	testDelete(NULL, 0, 0);
	testDelete(append(NULL, "ARM", 1), 0, 0);
	testDelete(append(NULL, "ARM", 1), 1, 1); // Index out of range; no delete
	testDelete(append(append(NULL, "RISC-V", 1), "ARM", 2), 0, 1);
	testDelete(append(append(NULL, "RISC-V", 1), "ARM", 2), 1, 1);
	testDelete(append(append(append(NULL, "Intel", 1), "RISC-V", 2), "ARM", 3), 1, 2);

	// Test search
	testSearch(NULL, "Curry", -1);
	testSearch(append(NULL, "Curry", 30), "Curry", 0);
	testSearch(append(append(NULL, "Green", 23), "Curry", 30), "Curry", 1);
	testSearch(append(append(NULL, "Green", 23), "Curry", 30), "Thompson", -1);
	testSearch(append(append(append(NULL, "Hield", 7), "Green", 23), "Curry", 30), "Green", 1);

	// Test reverse
	testReverse(NULL, NULL);
	testReverse(append(NULL, "Embedded", 1), append(NULL, "Embedded", 1));
	testReverse(append(append(NULL, "C", 2), "Embedded", 1), append(append(NULL, "Embedded", 1), "C", 2));
	testReverse(append(append(append(NULL, "AudioVideo", 3), "C", 2), "Embedded", 1), append(append(append(NULL, "Embedded", 1), "C", 2), "AudioVideo", 3));

	// Test findMiddle
	testFindMiddle(append(NULL, "A", 1), append(NULL, "A", 1));
	testFindMiddle(append(append(NULL, "A", 1), "B", 2), append(NULL, "A", 1));
	testFindMiddle(append(append(append(NULL, "A", 1), "B", 2), "C", 3), append(NULL, "B", 2));
	testFindMiddle(insert(insert(insert(insert(NULL, 0, "A", 1), 1, "B", 2), 2, "C", 3), 3, "D", 4), insert(NULL, 0, "B", 2));
	testFindMiddle(insert(insert(insert(insert(insert(NULL, 0, "A", 1), 1, "B", 2), 2, "C", 3), 3, "D", 4), 4, "E", 5), createNode("C", 3));

	Node* head = insert(insert(insert(NULL, 0, "A", 1), 1, "B", 2), 2, "C", 3);
	Node* temp = head;
	while (temp->next) { temp = temp->next; }
	temp->next = head; // create cycle
	testFindMiddle(head, createNode("B", 2));

	head = insert(insert(insert(insert(NULL, 0, "A", 1), 1, "B", 2), 2, "C", 3), 3, "D", 4);
	temp = head;
	while (temp->next) { temp = temp->next; }
	temp->next = head; // create cycle
	testFindMiddle(head, createNode("B", 2));

	// Test mergeSort
	head = insert(NULL, 0, "Mario", 1);
	Node* expected = insert(NULL, 0, "Mario", 1);
	testMergeSort(head, expected);

	head = insert(insert(NULL, 0, "Luigi", 2), 1, "Mario", 1);
	expected = append(append(NULL, "Mario", 1), "Luigi", 2);
	testMergeSort(head, expected);

	head = insert(insert(insert(NULL, 0, "Luigi", 2), 1, "Mario", 1), 2, "Wario", 3);
	expected = append(append(append(NULL, "Mario", 1), "Luigi", 2), "Wario", 3);
	testMergeSort(head, expected);

	head = insert(insert(insert(insert(NULL, 0, "Mario", 1), 1, "Luigi", 2), 2, "Waluigi", 4), 2, "Wario", 3);
	expected = append(append(append(append(NULL, "Mario", 1), "Luigi", 2), "Wario", 3), "Waluigi", 4);
	testMergeSort(head, expected);

	head = insert(insert(insert(insert(insert(NULL, 0, "Yoshi", 5), 1, "Wario", 3), 2, "Luigi", 2), 3, "Waluigi", 4), 4, "Mario", 1);
	expected = append(append(append(append(append(NULL, "Mario", 1), "Luigi", 2), "Wario", 3), "Waluigi", 4), "Yoshi", 5);
	testMergeSort(head, expected);

	//loadTestSort(10, 0, 100);
	//loadTestSort(100, 0, 100);
	loadTestSort(1000000, 0, 1000000000);
	//loadTestSort(100000000, 0, 1000000000); ~20 mins
}

void compareLists(Node* ptr1, Node* ptr2)
{
	while (ptr1 && ptr2)
	{
		assert(ptr1->val == ptr2->val);
		assert(strcmp(ptr1->id, ptr2->id) == 0);
		
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
	}

	assert(ptr1 == NULL && ptr2 == NULL);
}

Node* generateRandomList(size_t len, int min, int max)
{
	char randString[RAND_STR_LEN + 1];
	generate_random_string(randString, RAND_STR_LEN);
	int randInt = generate_random_int(min, max);

	Node* head = createNode(randString, randInt);
	Node* temp = head;
	for (size_t i = 1; i < len; i++)
	{
		generate_random_string(randString, RAND_STR_LEN);
		randInt = generate_random_int(min, max);

		temp->next = createNode(randString, randInt);
		temp = temp->next;
	}

	temp = NULL;
	return head;
}

void loadTestSort(size_t len, int min, int max)
{
	Node* head = generateRandomList(len, min, max);

	head = mergeSort(head);

	#if DEBUG
		printLinkedList(head);
	#endif
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
	while (ptr && i < idx)
	{
		ptr = ptr->next;
	}	

	// idx could be out of range... meaning no insert occurred
	if (i != idx) { return; } 

	assert(strcmp(ptr->id, s) == 0);
	assert(ptr->val == val);

	freeLinkedList(head);
} 

void testDelete(Node* head, int index, int expectedLen)
{
	Node* ptr = NULL;
	int actualLen = 0;

	head = deleteNode(head, index);

	ptr = head;
	while (ptr)
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

	compareLists(ptr1, ptr2);

	freeLinkedList(head);
	freeLinkedList(expected);
}

void testFindMiddle(Node* head, Node* expected)
{
	Node* mid = findMiddle(head);

	assert(mid->val == expected->val);
	assert(strcmp(mid->id, expected->id) == 0);

	freeLinkedList(head);
	freeLinkedList(expected);
}

void testMergeSort(Node* head, Node* expected)
{
	Node* ptr1 = expected;
	Node* ptr2 = NULL;

	head = mergeSort(head);
	ptr2 = head;

	compareLists(ptr1, ptr2);

	freeLinkedList(head);
	freeLinkedList(expected);
}
