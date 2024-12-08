#include <stdio.h>
#include <string.h>

#include "../../include/solutions.h"
#include "../../include/arena.h"

#define LENGTH 130
#define WIDTH 130

typedef enum _direction 
{
	NONE,
	NORTH,
	EAST,
	SOUTH,
	WEST
} Direction;

static int d[5] = { 0, -1, 1, 1, -1 };
static int path[130][130] = { 0 };
static int pathP2[130][130] = { 0 };
static Direction dirAtVisit[130][130] = { 0 };
static int spacesVisited = 1;
static int obsCount = 0;
static int x, y;

#define LOG_MOVEMENT(spacesVisited, visited, posX, posY, direction, pln) \
	do { \
		spacesVisited += !visited[posY][posX]; \
		visited[posY][posX] |= !visited[posY][posX]; \
		dirAtVisit[posY][posX] = direction; \
		pln += d[direction]; \
	} while (0) \

static int _should_end(int posX, int posY, Direction next)
{
	switch (next)
	{
		case NORTH:
			return posY == 0;
		case SOUTH:
			return posY == LENGTH - 1;
		case EAST:
			return posX == WIDTH - 1;
		case WEST:
			return posX == 0;
		default:
			return 0;
	}
}

static void _travel(char **lab, int *posX, int *posY, Direction dir, int partTwo)
{
	Direction next;
	path[*posY][*posX] |= !path[*posY][*posX];

	while (1)
	{
		int yMovement = dir == NORTH || dir == SOUTH;
		int withinBounds = yMovement ? 
			*posY - 1 >= 0 && *posY + 1 < LENGTH :
			*posX - 1 >= 0 && *posX + 1 < WIDTH;

		if (!withinBounds) break;

		int isObs = yMovement ?
			lab[*posY + d[dir]][*posX] == '#' :
			lab[*posY][*posX + d[dir]] == '#';
		int *plane = yMovement ? posY : posX;

		if (isObs) break;

		if (partTwo)
		{
			if (pathP2[*posY][*posX] && dirAtVisit[*posY][*posX] == dir)
			{
				obsCount++;
				return;
			}

			pathP2[*posY][*posX] |= !pathP2[*posY][*posX];
		}

		LOG_MOVEMENT(spacesVisited, path, *posX, *posY, dir, *plane);
	}

	spacesVisited += !path[*posY][*posX];
	next = dir == 4 ? NORTH : dir + 1;

	if (_should_end(*posX, *posY, dir)) return;

	_travel(lab, posX, posY, next, partTwo);
}

// brute force with a touch of thought... but just a touch.
static void _travel_part_two(char **lab, int partTwo)
{
	int r = 0;
	int c = 0;

	while (r < LENGTH)
	{
		if (c == WIDTH)
		{
			c = 0;
			r++;
		}
		else
		{
			int tx = x;
			int ty = y;

	 		memset(pathP2, 0, sizeof(pathP2));
			memset(dirAtVisit, 0, sizeof(dirAtVisit));

			if (!path[r][c] || lab[r][c] == '#') 
			{
				c++;
				continue;
			}

			char hold = lab[r][c];

			lab[r][c] = '#';

			_travel(lab, &tx, &ty, NORTH, partTwo);

			lab[r][c] = hold;

			c++; // lol
		}
	}
}

int day_6(int partTwo)
{
	FILE *f = fopen("./input/day6.txt", "r");
	char buffer[133];

	CHECK_FILE(f);

	Arena ar = a_new(LENGTH * WIDTH * sizeof(char *));
	char **lab = a_alloc(&ar, sizeof(char *) * 131, __alignof(char *));
	int startX = 0;
	int startY = 0;

	for (size_t i = 0; fgets(buffer, sizeof(buffer), f); i++)
	{
		char *start;

		buffer[strcspn(buffer, "\r\n")] = '\0';
		buffer[strcspn(buffer, "\r")] = '\0';
		lab[i] = a_strdup(&ar, buffer);

		if ((start = strchr(buffer, '^'))) 
		{
			x = start - buffer;
			y = i;
		}
	}

	startX = x;
	startY = y;

	_travel(lab, &startX, &startY, NORTH, partTwo);

	path[startY][startX] = 1; // log where I ended.

	if (partTwo) _travel_part_two(lab, partTwo);

	a_free(&ar);
	fclose(f);

	return partTwo ? obsCount : spacesVisited;
}
