#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_map
{
    int height;
    int width;
    char empty;
    char obstacle;
    char full;
    char **grid;
}   t_map;

bool parse_map(FILE *file, t_map *map);

#endif