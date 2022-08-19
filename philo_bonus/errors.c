#include <stdio.h>
#include <stdlib.h>

void	exit_program(const char *message)
{
	if (message == NULL)
		printf("Error\n");
	else
		printf("Error: %s\n", message);
	exit(1);
}