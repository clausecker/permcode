#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "permcode.h"

void print(unsigned char perm[PC_COUNT])
{
	size_t i;

	for (i = 0; i < PC_COUNT; i++)
		printf("%2d%c", perm[i], i == PC_COUNT - 1 ? '\n' : ' ');
}

int main()
{
	size_t i;
	unsigned char perm[PC_COUNT] = { 0 };

	srand(time(NULL));

	for (i = 0; i < PC_COUNT; i++)
		perm[i] = rand() % (SQ_COUNT - i);

	print(perm);
	decode(perm);
	print(perm);
	encode(perm);
	print(perm);

	return (0);
}
