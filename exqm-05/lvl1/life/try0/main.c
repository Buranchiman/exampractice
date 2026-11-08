#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "life.h"

void free_board(t_game *game)
{
	if (game->board)
	{
		for (int i = 0; i < game->height; i++)
		{
			if (game->board[i])
				free(game->board[i]);
		}
		free(game->board);
	}
}

int	init_game(t_game *game, char **arv)
{
	int i = 0;
	int	j;
	game->width = atoi(arv[1]);
	game->height = atoi(arv[2]);
	game->iterations = atoi(arv[3]);
	if (!game->width || !game->height)
		return (0);
	game->board = (char **)malloc(sizeof(char *) * game->height);
	if (!game->board)
		return (0);
	while (i < game->height)
	{
		game->board[i] = (char *)malloc(sizeof(char) * game->width);
		if (!game->board[i])
			return (free_board(game), 0);
		j = 0;
		while (j < game-> width)
		{
			game->board[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (1);
}

void fill_board(t_game *game)
{
	char c;
	bool	draw = false;
	int	x = 0;
	int y = 0;

	while (read(STDIN_FILENO, &c, 1) == 1)
	{
		switch (c)
		{
			case 'x' :
			{
				draw = !draw;
				break;
			}
			case 'w' :
			{
				if (y > 0)
					y--;
				break;
			}
			case 'a' :
			{
				if (x > 0)
					x--;
				break;
			}
			case 's' :
			{
				if (y < game->height - 1)
					y++;
				break;
			}
			case 'd' :
			{
				if (x < game->width - 1)
					x++;
				break;
			}
			default :
				break;
		}
		if (draw)
			game->board[y][x] = '0';
	}
}

int	count_neighbors(t_game *game, int y, int x)
{
	int	count = 0;
	for (int i = -1; i < 2; i ++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (i == 0 && j == 0)
				continue;

			int currx = x + j;
			int curry = y + i;
			if ((currx >= 0 && currx < game->width) && (curry >= 0 && curry < game->height) && game->board[y + i][x + j] == '0')
				count++;
		}
	}
	return (count);
}

int	play_game(t_game *game)
{
	char **tmp;
	tmp = (char **)malloc(sizeof(char *) * game->height);
	if (!tmp)
		return (0);
	//printf("Passed big map alloc\n");
	for (int i = 0; i < game->height; i++)
	{
		tmp[i] = (char *)malloc(sizeof(char) * game->width);
		if (!tmp[i])
			return (free_board(game), 0);
		// for (int j = 0; j < game->width; j++)
		// {
		// 	tmp[i][j] = game->board[i][j];
		// }
	}
	for (int i = 0; i < game->height; i++)
	{
		for (int j = 0; j < game->width; j++)
		{
			int neighbors = count_neighbors(game, i, j);
			if (game->board[i][j] == '0')
			{
				//printf("for cell nb of neighbors is %d\n", neighbors);
				if (neighbors == 2 || neighbors == 3)
					tmp[i][j] = '0';
				else
					tmp[i][j] = ' ';
			}
			else
			{
				if (neighbors == 3)
					tmp[i][j] = '0';
				else
					tmp[i][j] = ' ';
			}
		}
	}
	free_board(game);
	game->board = tmp;
	return (1);
}

void print_board(t_game *game)
{
	for (int i = 0; i < game->height; i++)
	{
		for (int j = 0; j < game->width; j++)
			putchar(game->board[i][j]);
		putchar('\n');
	}
}

int	main(int arc, char **arv)
{
	t_game game;

	if (arc != 4)
		return (1);
	if (!init_game(&game, arv))
		return(1);
	fill_board(&game);
	for (int i = 0; i < game.iterations; i++)
	{
		if (!play_game(&game))
			return (1);
	}
	//printf("Reached print board\n");
	print_board(&game);
	free_board(&game);
	return (0);
}
