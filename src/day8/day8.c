#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/solutions.h"
#include "../../include/arena.h"

#define BUFFER_SIZE 53
#define LENGTH 50
#define WIDTH 50

typedef struct _point
{
	int x;
	int y;
} Point;

static int isPartTwo;

static short antinodes[LENGTH][WIDTH] = { 0 };
static short antinodeCount = 0;

static void _find_antinodes(Arena *ar, Point *first, Point *second);
static void _find_additional_antinodes(short x, short y, short dx, short dy, short beforeStart);

static void _find_antenna_match(Arena *ar, char **grid, char antenna, short posY, short posX)
{
	Point *first = a_alloc(ar, sizeof(Point), __alignof(Point));
	Point *second = a_alloc(ar, sizeof(Point), __alignof(Point));

	first->x = posX;
	first->y = posY;
	second->x = -1;
	second->y = -1;

	for (int i = posY + 1; i < LENGTH; i++)
	{
		char * start;

		if (!(start = strchr(grid[i], antenna))) continue;

		second->x = start - grid[i];
		second->y = i;

		_find_antinodes(ar, first, second);

		second->x = -1;
		second->y = -1;
	}
}

static void _find_antinodes(Arena *ar, Point *first, Point *second)
{
	Point *a = a_alloc(ar, sizeof(Point), __alignof(Point));
	Point *b = a_alloc(ar, sizeof(Point), __alignof(Point));

	short x1 = first->x;
	short y1 = first->y;
	short x2 = second->x;
	short y2 = second->y;
	short dx = x2 - x1;
	short dy = y2 - y1;

	short xWithinBounds = (x1 - dx >= 0) && (x1 + abs(dx) < WIDTH);
	short yWithinBounds = (y1 - dy >= 0) && (y1 + dy < LENGTH);
	
	a->x = xWithinBounds ? x1 - dx : -1;
	a->y = yWithinBounds ? y1 - dy : -1;
	
	if (a->x != -1 && a->y != -1)
	{
		// log and increment antinodes for part one
		antinodeCount += !antinodes[a->y][a->x];
		antinodes[a->y][a->x] = 1;

		// find, log and increment additional antinodes
		// for part two
		_find_additional_antinodes(
			a->x,
			a->y,
			second->x - first->x,
			second->y - first->y,
			1
		);
	}

	xWithinBounds = (x2 - abs(dx) >= 0) && (x2 + dx < WIDTH);
	yWithinBounds = (y2 - dy >= 0) && (y2 + dy < LENGTH);
	
	b->x = xWithinBounds ? x2 + dx : -1;
	b->y = yWithinBounds ? y2 + dy : -1;
	
	if (b->x != -1 && b->y != -1)
	{
		antinodeCount += !antinodes[b->y][b->x];
		antinodes[b->y][b->x] = 1;

		_find_additional_antinodes(
			b->x,
			b->y,
			second->x - first->x,
			second->y - first->y,
			0
		);
	}
}

static void _find_additional_antinodes(short x, short y, short dx, short dy, short beforeStart)
{
	if (!isPartTwo) return;

	short xWithinBounds;
	short yWithinBounds;

	while (1)
	{
		if (beforeStart)
		{
			xWithinBounds = (x - dx >= 0) && (x + abs(dx) < WIDTH);
			yWithinBounds = (y - dy >= 0) && (y + dy < LENGTH);
		}
		else
		{
			xWithinBounds = (x - abs(dx) >= 0) && (x + dx < WIDTH);
			yWithinBounds = (y - dy >= 0) && (y + dy < LENGTH);
		}

		if (!xWithinBounds || !yWithinBounds) break;

		x = beforeStart ? x - dx : x + dx;
		y = beforeStart ? y - dy : y + dy;

		antinodeCount += !antinodes[y][x];
		antinodes[y][x] = 1;
	}
}

int day_8(short partTwo)
{
	FILE *f = fopen("./input/day8.txt", "r");
	char buffer[BUFFER_SIZE]; // line length + \r + \n + \0

	CHECK_FILE(f);

	isPartTwo = partTwo;

	Arena ar = a_new(LENGTH * WIDTH);
	Arena pointAr = a_new(sizeof(Point));
	char **grid = a_alloc(&ar, sizeof(char *) * LENGTH, __alignof(char *));

	for (size_t i = 0; fgets(buffer, sizeof(buffer), f); i++)
	{
		buffer[strcspn(buffer, "\r")] = '\0';
		buffer[strcspn(buffer, "\r\n")] = '\0';

		grid[i] = a_strdup(&ar, buffer);
	}

	for (size_t i = 0; i < LENGTH; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			char antenna = grid[i][j];

			if (antenna == 46) continue;

			_find_antenna_match(&pointAr, grid, antenna, i, j);

	   		if (partTwo) {
				antinodeCount += !antinodes[i][j];
				antinodes[i][j] = 1;
			}
		}
	}

	a_free(&pointAr);
	a_free(&ar);
	fclose(f);

	return antinodeCount;
}
