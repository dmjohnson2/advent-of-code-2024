#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../include/solutions.h"
#include "../../include/arena.h"

#define SIZE 100

#define SWAP(x, y) \
	do { \
		int tmp = x; \
		x = y; \
		y = tmp; \
	} while(0)\

static int _check_update(int rules[SIZE][SIZE], int *update, size_t updateCnt)
{
	size_t i = 0;
	size_t j = 0;

	while (i < updateCnt)
	{
		if (i == j)
		{
			j++;
			continue;
		}
		else if (i > j && rules[update[i]][update[j]]) return 0;
		else if (i < j && rules[update[j]][update[i]]) return 0;
		else if (j == updateCnt)
		{
			j = 0;
			i++;
		}
		else j++;
	}

	return update[updateCnt / 2];
}

static int _fix_update(int rules[SIZE][SIZE], int *update, size_t updateCnt)
{
	size_t i = 0;
	size_t j = 0;

	while (i < updateCnt)
	{
		if (i == j)
		{
			j++;
			continue;
		}
		else if (i > j && rules[update[i]][update[j]]) SWAP(update[i], update[j]);
		else if (i < j && rules[update[j]][update[i]]) SWAP(update[i], update[j]);
		else if (j == updateCnt)
		{
			j = 0;
			i++;
		}
		else j++;
	}

	return update[updateCnt / 2];
}

int day_5(int partTwo)
{
	FILE *f = fopen("./input/day5.txt", "r");
	char buffer[150];

	CHECK_FILE(f);

	Arena updateAr = a_new(sizeof(int) * 30);
	int *update = a_alloc(&updateAr, sizeof(int) * 25, __alignof(int));
	int rules[100][100] = { 0 };
	int result = 0;
	int fixedResult = 0;

	while (fgets(buffer, sizeof(buffer), f))
	{
		int a = 0;
		int b = 0;

		if (buffer[2] == '|') 
		{
			if (sscanf(buffer, "%d|%d\n", &a, &b) == 2) rules[a][b] = 1;
	  	
			continue;
		}

		if(strcmp(buffer, "\r\n") == 0) continue;
		
		char *tok = strtok(buffer, ",");
		size_t i;

		for (i = 0; tok; i++)
		{
			update[i] = atoi(tok);
			tok = strtok(NULL, ",");
		}

		update[i] = 0;

		int res = _check_update(rules, update, i);

		result += res;

		if (res == 0 && partTwo) fixedResult += _fix_update(rules, update, i);
	}

	fclose(f);
	a_free(&updateAr);

	return partTwo ? fixedResult : result;
}
