#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../include/solutions.h"

static void _match(char *buf, long *res);

long day_3(void)
{
	FILE *f = fopen("./input/day3.txt", "r");
	char buffer[4096];
	long res = 0;

	// woo more nested loops.
	while(fgets(buffer, sizeof(buffer), f))
	{
		_match(buffer, &res);
	}

	fclose(f);

	return res;
}

static void _match(char *buf, long *res)
{
	char *st = buf;

	while ((st = strstr(st, "mul")))
	{
		if (*st == '\0') return;

		char a[4];
		char b[4];
		char closeParen;

		// %d eats leading whitespace, still matches cases like mul( 22, 32).
		int matches = sscanf(st, "mul(%3[^, ],%3[^) ]%c", a, b, &closeParen);
		
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
