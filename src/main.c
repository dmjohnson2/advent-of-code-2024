#include <stdio.h>

#include "../include/solutions.h"

int main(void)
{
#define PRINT_DAY(text, fmt, day, isPart2) \
	printf(text" "fmt, day_##day(isPart2));
#include "../include/display_table.h"
#undef PRINT_DAY
}
