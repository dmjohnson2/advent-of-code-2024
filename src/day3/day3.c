#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../include/solutions.h"

static void _match(char *buf, long *res, int partTwo);
static void _check_status(int pos, char *buf);

static int status = 1; 

long day_3(short partTwo)
{
	FILE *f = fopen("./input/day3.txt", "r");
	char buffer[4096];
	long res = 0;

	if (!f) 
	{
		fprintf(stderr, "Uh, where's the input? Do you know what you're doing?\n");
		exit(EXIT_FAILURE);
	}

	// woo more nested loops.
	while(fgets(buffer, sizeof(buffer), f))
	{
		_match(buffer, &res, partTwo);
	}

	fclose(f);

	return res;
}

static void _match(char *buf, long *res, int partTwo)
{
	char *st = buf;

	while ((st = strstr(st, "mul")))
	{
		if (*st == '\0') return;

		if (partTwo) _check_status(st - buf, buf);

		if (!status) 
		{
			st++;
			continue;
		}

		char a[4];
		char b[4];
		char closeParen;

		// %d eats leading whitespace, still matches cases like mul( 22, 32).
		int matches = sscanf(st, "mul(%3[0-9],%3[0-9]%c", a, b, &closeParen);
		
		if (matches == 3)
		{
			if (closeParen != ')')
			{
				st++;
				continue;
			}

			st = strchr(st, ')');
			*res += (atoi(a) * atoi(b));
		}
		else st++;
	}
}

// Listen, you don't like this, I don't like this,
// nobody likes this. I didn't know that these problems
// had a part 2 until the 3rd day. I wasn't prepared
// and I have no desire to imporve this.
//
// sue me
static void _check_status(int pos, char *buf)
{
	char *st;
	int closestDo;
	int closestDont;

	st = strstr(buf, "do()");
	closestDo = st ? st - buf : -1;
	closestDo = closestDo > pos ? -1 : closestDo;

	while (st && closestDo < pos && (st = strstr(st, "do()")))
	{
		int idx = st - buf;

		if (idx < pos) 
		{
			closestDo = idx; 
			st++;
		}
		else break;
	}
	
	st = strstr(buf, "don't()");
	closestDont = st ? st - buf : -1;
	closestDont = closestDont > pos ? -1 : closestDont;

	while (st && closestDont < pos && (st = strstr(st, "don't()")))
	{
		int idx = st - buf;

		if (idx < pos) 
		{
			closestDont = idx; 
			st++; 
		}
		else break;
	}

	if (closestDo == -1 && closestDont == -1) return;

	status = closestDo > closestDont;
}
