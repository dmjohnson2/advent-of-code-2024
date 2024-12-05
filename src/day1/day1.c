#include <stdio.h>
#include <stdlib.h>

#include "../../include/solutions.h"

#define SIZE 1000

static int _cmp_func(const void *a, const void *b)
{
	int x = *(int *)a;
	int y = *(int *)b;

	return x - y;
}

int day_1(int partTwo)
{
	FILE *f = fopen("./input/day1.txt", "r");
	char buffer[256];
	size_t count = 0;
	unsigned int sizeMult = 1;
	unsigned int totalDiff = 0;	
	unsigned int simScore = 0;

	if (!f) 
	{
		fprintf(stderr, "Uh, where's the input? Do you know what you're doing?\n");
		exit(EXIT_FAILURE);
	}

	int *left = malloc(sizeof(int) * SIZE);
	int *right = malloc(sizeof(int) * SIZE);

	for (; fgets(buffer, sizeof(buffer), f); count++)
	{
		if (count >= SIZE)
		{
			left = realloc(left, sizeof(int) * (SIZE * ++sizeMult));
			right = realloc(right, sizeof(int) * (SIZE * sizeMult));

			if (!left || !right) fprintf(stderr, "sad face\n");
		}
		sscanf(buffer, "%d   %d\n", &left[count], &right[count]);
	}

	fclose(f);

	qsort(left, count, sizeof(int), _cmp_func);
	qsort(right, count, sizeof(int), _cmp_func);

	for (size_t j = 0; j < count; j++)
	{
		totalDiff += abs(left[j] - right[j]);
	}

	if (!partTwo) return totalDiff;

	size_t countLeft = 0;
	size_t countRight = 0;
	unsigned int occ = 0;

	while (countLeft < count && countRight < count)
	{
		if (left[countLeft] == right[countRight])
		{
			occ++;
			countRight++;
		}
		else if (left[countLeft] < right[countRight])
		{
			simScore = simScore + (left[countLeft] * occ);
			countLeft++;
			occ = 0;
		}
		else
		{
			countRight++;
		}
	}

	free(left);
	free(right);

	return simScore;
}
