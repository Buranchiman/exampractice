#ifndef LIFE_H
#define LIFE_H

#include <stdbool.h>

typedef struct s_game
{
	int	width;
	int height;
	int iterations;
	char **board;
}	t_game;

#endif
