/*
	BULLS AND COWS game
	source code released in the public domain without warranty of any kind

	by Lubomir I. Ivanov <neolit123@gmail.com>, 2013

	gcc bulls.c -W -ansi -pedantic -O1 -o bulls.exe -s
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define LEN 4 /* number of digits to use */

void result(char *u, char *r, unsigned n)
{
	short j, i = 0, b = 0, k = 0;
	for (i = 0; i < LEN; i++) {
		for (j = 0; j < LEN; j++) {
			if (u[i] == r[j])
				(i == j) ? b++ : k++;
		}
	}
	printf("\t%uB%uK (%u)\n", b, k, n);
}

unsigned digit_unique(char c, char *u, short skip)
{
	short i;
	for (i = 0; i < LEN; i++) {
		if (c == u[i] && i != skip)
			return 0;
	}
	return 1;
}

unsigned number_valid(char *u)
{
	short i;
	for (i = 0; i < LEN; i++) {
		if (u[i] < 0 || u[i] > 9 || !digit_unique(u[i], u, i))
			return 0;
	}
	return 1;
}

int main(void)
{
	const char z = 0x30; /* offset of ASCII '0' */
	char c;
	char u[LEN], r[LEN];
	short i;
	unsigned n;

	srand(time(NULL));

	printf("\nBULLS AND COWS\n" \
		"by Lubomir I. Ivanov <neolit123@gmail.com>, 2014\n\n" \
		"gameplay:\n" \
		"\t - you win if you find %u bulls (%uB0K)\n" \
		"\t - all digits in the number must be unique\n" \
		"\t - number cannot start with 0 but can contain it\n" \
		"\t - if you enter more than %u digits the rest will be ignored\n" \
		"\t - to exit press 'ctrl + c'\n", LEN, LEN, LEN);
	do { /* game loop */
		printf("\nguess the %u digit number:\n", LEN);
		/* prepare the result */
		r[0] = 1 + rand() % 9;
		for (i = 1; i < LEN; i++) {
			do {
				c = rand() % 10;
			} while (!digit_unique(c, r, -1));
			r[i] = c;
		}
		n = 1;
		for (i = 0; i < LEN; i++)
			u[i] = 0;
		/* repeat until user digits match the result */
		while (*(unsigned *)&u != *(unsigned *)&r) {
			i = 0;
			do {
				c = getchar();
				if (i < LEN) {
					u[i] = c - z;
					i++;
				}
			} while (c != '\n');
			if (i > 1) { /* validate only if the buffer is filled */
				if (number_valid(u))
					result(u, r, n++);
				else
					puts("* incorrect digits");
			}
		}
		printf("\nyou win!\n\ncontinue playing [y/n]: ");
	} while (getchar() == 'y');

	return 0;
}
