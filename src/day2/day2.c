#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/solutions.h"
#include "../../include/arena.h"

#define SIZE 10 
#define MAX_DIFF 3

static int * _remove_level(Arena *arena, int *report, size_t idx, size_t tokCount)
{
	int *newReport = a_alloc(arena, sizeof(int) * tokCount - 1, __alignof(int));
	int newIdx = 0;

	for (size_t i = 0; i < tokCount; i++)
	{
		if (i == idx) continue;

		newReport[newIdx++] = report[i];
	}

	return newReport;
}

static int _check_safety(int *report, size_t tokCount)
{
	int desc = 0;
	int asc = 0;

	for (size_t i = 0; i < tokCount - 1; i++)
	{
		int diff = abs(report[i] - report[i + 1]);

		if (report[i] > report[i + 1]) asc++;
		else if (report[i] < report[i + 1]) desc++;
		else return i;

		if ((diff > MAX_DIFF) || (asc && desc)) return i;
	}

	return -1;
}

int day_2(short partTwo)
{
	FILE *f = fopen("./input/day2.txt", "r");

	char buffer[256];
	int safeReports = 0;

	if (!f) 
	{
		fprintf(stderr, "Uh, where's the input? Do you know what you're doing?\n");
		exit(EXIT_FAILURE);
	}

	Arena arena = a_new(512);

	while (fgets(buffer, sizeof(buffer), f))
	{

		int *rpt = a_alloc(&arena, sizeof(int) * SIZE, __alignof(int));
		int tokCount = 0;
		char *tok;

		tok = strtok(buffer, " ");

		for (; tok; tokCount++)
		{
			rpt[tokCount] = atoi(tok);
			tok = strtok(NULL, " ");
		}

		int res = _check_safety(rpt, tokCount);

		if (res == -1)
		{
			safeReports++;
			continue;
		}

		if (!partTwo) continue;

		if (_check_safety(_remove_level(&arena, rpt, res, tokCount), tokCount - 1) == -1 ||
			_check_safety(_remove_level(&arena, rpt, res + 1, tokCount), tokCount - 1) == -1 ||
			_check_safety(_remove_level(&arena, rpt, res - 1, tokCount), tokCount - 1) == -1)
		{
			safeReports++;
		}
	}

	a_free(&arena);
	fclose(f);

	return safeReports;
}
