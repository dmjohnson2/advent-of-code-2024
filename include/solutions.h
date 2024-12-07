#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stdlib.h>

// This could, and probably should, be an inline function.
// I'm' not leaving this one up to the compiler though.
#define CHECK_FILE(f) \
	do { \
		if (!f) \
		{ \
			fprintf(stderr, "Uh, where's the input? Do you know what you're doing?\n"); \
			exit(EXIT_FAILURE); \
		} \
	} while (0) \

int day_1(int partTwo);
int day_2(int partTwo);
long day_3(int partTwo);
int day_4(int partTwo);
int day_5(int partTwo);

#endif
