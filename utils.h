#ifndef UTILS_H 
#define UTILS_H
#define MAXLINE 31

void printMenu(void);

int getIndex(void);

void getStringID(char buffer[], int lim);

int getNodeValue(void);

/* K&R C Programming Language 2nd Edition Page 29 */
int getLine(char s[], int lim); /* read a line into s, return length */

int getIntFromString(void);

#endif
