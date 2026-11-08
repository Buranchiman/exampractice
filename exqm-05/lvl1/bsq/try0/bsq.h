#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_map
{
    int  rows;
    int  cols;
    char empty;
    char obstacle;
    char full;
    char **grid;
}   t_map;

bool solve(t_map *map);
bool parse_map(FILE *file, t_map *m);
void    free_map(t_map *m);
void print_map(t_map *map);

#endif
