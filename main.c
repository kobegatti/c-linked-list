#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "node.h"

#define MAXLINE 10

/* Function Prototypes */
void printMenu(void);

// K&R C Programming Language 2nd Edition Page 29
int getLine(char s[], int lim); /* read a line without '\n' into s, return length */

int getIntFromString(void);

int main(void)
{
	Node* head = NULL;
	char line[MAXLINE];
	int n = 0;
	
	while(n != EXIT)
	{
		printf("\nStarter-Linked-List:\n");
		printMenu();

		printf("Select an option: ");
		n = getIntFromString();

		switch(n)
		{
			int val = -1;
			case APPEND:
				printf("Enter a value (int): ");
				val = getIntFromString();

				printf("Enter a string id (%d char max): ", MAXLINE);
				getLine(line, MAXLINE);

				head = append(head, val, line);
				break;
			case PRINT:
				printList(head);
				break;
			case EXIT:
				printf("Exiting program...\n");
				break;
			default:
				fprintf(stderr, "Invalid selection...\n");
				break;
		}
	}

	freeLinkedList(head);

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
		fprintf(stderr, "No valid int conversion from '%s'\n", line);
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
	return i;
}

