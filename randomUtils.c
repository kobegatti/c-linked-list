#include <stdlib.h>
#include "randomUtils.h"

static const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
static const size_t charset_size = sizeof(charset) - 1;

void generate_random_string(char* str, size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		int key = rand() % charset_size;
		str[i] = charset[key];
	}

	str[len] = '\0';
}

int generate_random_int(int min, int max)
{
	return min + rand() % (max - min + 1);
}
