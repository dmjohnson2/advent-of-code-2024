#include <stdio.h>
#include <string.h>

#include "../../include/arena.h"
#include "../../include/solutions.h"

#define BUF_SIZE 1024
#define CHAR_A 'A'

static int _search_ln(char *line)
{
	int res = 0;

	char *st = line;

	for (; (st = strstr(st, "XMAS")); st++, res++);

	st = line;

	for (; (st = strstr(st, "SAMX")); st++, res++);

	return res;
}

// this is dumb lmao
static int _search_dgl(char **ws, int w, int h)
{
	int res = 0;
	int r = 0;
	int c = 0;

	while (r < h)
	{
		if (c == w)
		{
			r++;
			c = 0;
		}
		else
		{
			int ltrOk = c + 3 <= w - 1 && r + 3 <= h - 1;
			int rtlOk = c - 3 >= 0 && r + 3 <= h - 1;

			if (ltrOk)
			{
				char token[5] = 
					{ ws[r][c], ws[r + 1][c + 1], ws[r + 2][c + 2], ws[r + 3][c + 3], '\0' };
				
				if (strcmp("XMAS", token) == 0 || strcmp("SAMX", token) == 0) res++;
			}

			if (rtlOk)
			{
				char token[5] = 
					{ ws[r][c], ws[r + 1][c - 1], ws[r + 2][c - 2], ws[r + 3][c - 3], '\0' };
				
				if (strcmp("XMAS", token) == 0 || strcmp("SAMX", token) == 0) res++;
			}

			c++;
		}
	}

	return res;
}

static int _search_pt2(char **ws, int w, int h)
{
	int res = 0;
	int r = 0;
	int c = 0;

	while (r < h)
	{
		if (c == w)
		{
			r++;
			c = 0;
		}
		else if (ws[r][c] == CHAR_A)
		{
			int colOk = c >= 1 && c <= w - 2;
			int rowOk = r >= 1 && r <= h - 2;

			if (colOk && rowOk)
			{
				char leftToRight[4] =
					{ ws[r - 1][c - 1], ws[r][c], ws[r + 1][c + 1], '\0' };
				char rightToLeft[4] = 
					{ ws[r - 1][c + 1], ws[r][c], ws[r + 1][c - 1], '\0' };

				int ltrMatches = strcmp("MAS", leftToRight) == 0 || strcmp("SAM", leftToRight) == 0;
				int rtlMatches = strcmp("MAS", rightToLeft) == 0 || strcmp("SAM", rightToLeft) == 0;

				if (ltrMatches && rtlMatches) res++;
			}

			c++;
		}
		else c++;
	}

	return res;
}

static int _search_vrt(char **ws, size_t cnt)
{
	char vrtCh[cnt + 1];
	size_t lineLength = strlen(*ws);
	size_t r = 0, c = 0;
	int res = 0;

	while (c < lineLength)
	{
		if (r == cnt)
		{
			vrtCh[cnt] = '\0';

			res += _search_ln(vrtCh);

			c++;
			r = 0;
		}
		else 
		{
			vrtCh[r] = ws[r][c];
			r++;
		}
	}

	return res;
}

int day_4(short partTwo)
{
	FILE *f = fopen("./input/day4.txt", "r");
	char buffer[BUF_SIZE];
	size_t cnt = 0;
	int res = 0;
	int lineLength;
	
	CHECK_FILE(f);

	Arena ar = a_new(BUF_SIZE * sizeof(char *));
	char **ws = a_alloc(&ar, sizeof(char *) * 1000, __alignof(char *));

	for (; fgets(buffer, sizeof(buffer), f); cnt++)
	{
		buffer[strcspn(buffer, "\r\n")] = 0;
		ws[cnt] = a_strdup(&ar, buffer);	
		if (!partTwo) res += _search_ln(ws[cnt]);
	}

	lineLength = strlen(ws[0]);

	if (partTwo)
	{
		res = _search_pt2(ws, lineLength, cnt);

		fclose(f);
		a_free(&ar);
		return res;
	}

	res += _search_vrt(ws, cnt);
	res += _search_dgl(ws, lineLength, cnt);

	a_free(&ar);
	fclose(f);

	return res;
}
