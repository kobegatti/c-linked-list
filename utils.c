#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "utils.h"

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
		fprintf(stderr,
			"Errno %d: No valid int conversion from '%s'\n", 
			errno, line);
		return -1;
	}

	return i;
}

/* K&R C Programming Language 2nd Edition Page 29 */
int getLine(char s[], int lim)
{
	int c, i;

	for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
	{
		s[i] = c;
	}

	s[i] = '\0';

	/* If input was too long, flush the remainder of the input buffer */
	if (c != '\n')
	{
		while ((c = getchar()) != EOF && c != '\n');
	}

	return i;
}
