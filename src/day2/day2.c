#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/solutions.h"

#define SIZE 10 
#define MAX_DIFF 3

static int _check_safety(int *report, int tokCount, int *safeReports)
{
	int desc = 1;
	int asc = 1;

	for (size_t i = 0; i < (size_t)tokCount - 1; i++)
	{
		int diff = abs(report[i] - report[i + 1]);

		if (report[i] > report[i + 1]) asc = 0;
		else if (report[i] < report[i + 1]) desc = 0;
		else return 0;

		if (diff > MAX_DIFF) return 0;
	}

	if (!asc && !desc) return 0;

	(*safeReports)++;

	return 1;
}

int day_2(void)
{
	FILE *f = fopen("./input/day2.txt", "r");
	char buffer[256];
	size_t reportCount = 0;
	int safeReports = 0;

	if (!f) 
	{
		fprintf(stderr, "Uh, where's the input? Do you know what you're doing?\n");
		exit(EXIT_FAILURE);
	}

	for (; fgets(buffer, sizeof(buffer), f); reportCount++)
	{
		int *report = malloc(sizeof(int) * SIZE);
		int tokCount = 0;
		char *tok;

		tok = strtok(buffer, " ");

		for (; tok; tokCount++)
		{
			report[tokCount] = atoi(tok);
			tok = strtok(NULL, " ");
		}

		_check_safety(report, tokCount, &safeReports);
		
		free(report);
	}

	fclose(f);

	return safeReports;
}
