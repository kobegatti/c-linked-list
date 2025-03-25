#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "node.h"
#include "utils.h"

int main(void)
{
	Node* head = NULL;
	char line[MAXLINE];
	int n = -1;
	
	while (n != EXIT)
	{
		int idx = -1, val = -1;

		printf("\nStarter-Linked-List:\n");
		printMenu();

		printf("Select an option: ");
		while (getIntFromString(&n))
		{
			printf("Select an option: ");
		}

		switch(n)
		{
			case APPEND:
				getStringID(line, MAXLINE);
				val = getNodeValue();

				head = append(head, line, val);
				break;
			case INSERT:
				idx = getIndex();
				getStringID(line, MAXLINE);
				val = getNodeValue();

				head = insert(head, idx, line, val);
				break;
			case DELETE:
				idx = getIndex();

				head = deleteNode(head, idx);
				break;
			case PRINT:
				printLinkedList(head);
				break;
			case REVERSE:
				head = reverse(head);
				break;
			case SEARCH:
				getStringID(line, MAXLINE);
				
				idx = search(head, line);
				if (idx < 0)
				{
					printf("id '%s' not found\n", line);
				}
				else
				{
					printf("id '%s' found at index %d\n", line, idx);
				}
				break;
			case SORT:
				head = mergeSort(head);
				break;
			case EXIT:
				printf("Exiting program...\n");
				break;
			default:
				fprintf(stderr, "%d is not a valid selection...\n", n);
				break;
		}
	}

	printf("Freed %d node(s)...\n", freeLinkedList(head));

	return EXIT_SUCCESS;
}
