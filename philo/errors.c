#include <stdio.h>
#include "colors.h"
#include <stdbool.h>

bool	exit_program(char *message)
{
	if (message == NULL)
		printf("Error\n");
	else
		printf("Error: %s\n", message);
	return (false);
}
