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

#define SOL(type, day) \
	type day_##day(int partTwo);
#include "../include/solutions_table.h"
#undef SOL
#endif
