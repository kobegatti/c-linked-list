#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "node.h"

#define MAXLINE 31 

/* Function Prototypes */
void printMenu(void);

int getIndex(void);

void getStringID(char buffer[], int lim);

int getNodeValue(void);

// K&R C Programming Language 2nd Edition Page 29
int getLine(char s[], int lim); /* read a line into s, return length */

int getIntFromString(void);

int main(void)
{
	Node* head = NULL;
	char line[MAXLINE];
	int n = -1;
	
	while(n != EXIT)
	{
		int idx = -1, val = -1;

		printf("\nStarter-Linked-List:\n");
		printMenu();

		printf("Select an option: ");
		n = getIntFromString();

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

				head = delete(head, idx);
				break;
			case PRINT:
				printList(head);
				break;
			case REVERSE:
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

void printMenu(void)
{
	printf("1. Append\n");
	printf("2. Insert\n");
	printf("3. Delete\n");
	printf("4. Print\n");
	printf("5. Reverse\n");
	printf("6. Search\n");
	printf("7. Exit\n");
}

int getIndex(void)
{
	int idx = -1;

	while(idx < 0)
	{
		printf("Enter a node index (zero-based int): ");
		idx = getIntFromString();
	}
	printf("Node index = %d\n", idx);

	return idx;
}

void getStringID(char buffer[], int lim)
{
	printf("Enter a string id (%d char max): ", MAXLINE);
	getLine(buffer, lim);
	printf("Node id = %s\n", buffer);
}

int getNodeValue(void)
{
	int val;

	printf("Enter a node value (int): ");
	val = getIntFromString();
	printf("Node value = %d\n", val);

	return val;
}

int getIntFromString(void)
{
	char line[MAXLINE];
	char* end;
	errno = 0;
	int i;

	getLine(line, MAXLINE);
	i = strtol(line, &end, 10);

	if (errno == ERANGE || end == line)
	{
		fprintf(stderr, "Errno %d: No valid int conversion from '%s'\n", errno, line);
		return -1;
	}

	return i;
}

// K&R C Programming Language 2nd Edition Page 29
int getLine(char s[], int lim)
{
	int c, i;

	for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
	{
		s[i] = c;
	}

	s[i] = '\0';

    // If the input was too long, flush the remainder of the input buffer
    if (c != '\n') 
	{
        while ((c = getchar()) != EOF && c != '\n');
	}

	return i;
}

