#include <stdio.h>
#include <stdlib.h>

#define EXIT_NUM 5
#define MAXLINE 100

/* Function Prototypes */
void printMenu(void);

// K&R C Programming Language 2nd Edition Page 29
int getLine(char s[], int lim); /* read a line without '\n' into s, return length */


int main(void)
{
	char line[MAXLINE];
	char* end;
	int n = 0;
	
	while(n != EXIT_NUM)
	{
		printf("\nStarter-Linked-List:\n");
		printMenu();

		printf("Enter a number: ");
		getLine(line, MAXLINE);
		n = strtol(line, &end, 10);

		switch(n)
		{
			case 1:
				printf("Insert node...\n");
				break;
			case EXIT_NUM:
				printf("Exiting program...\n");
				break;
			default:
				printf("Invalid selection...\n");
				break;
		}
	}

	return 0;
}

void printMenu(void)
{
	printf("1. Insert a node\n");
	printf("\n");
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
