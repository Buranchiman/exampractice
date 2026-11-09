#include "bsq.h"

bool is_printable(char c)
{
    if ( c < ' ' || c > 126)
        return (false);
    return (true);
}

bool parse_header(char *line, size_t len, t_map *map)
{
    if (line[len - 1] != '\n' || line[len - 3] != ' ' || line[len - 5] != ' ' || line[len - 7] != ' ')
        return (false);
    map->full = line[len - 2];
    map->obstacle = line[len - 4];
    map->empty = line[len - 6];
    long total = 0;
    int i= 0;
    while (line[i] >= '0' && line [i] <= '9')
    {
        total = total * 10 + line[i] - '0';
        i++;
        if (total > __INT32_MAX__)
            return (false);
    }
    if (total <= 0)
        return (false);
    map->height = total;
    if (map->obstacle == map->empty || map->obstacle == map->full || map->empty == map->full)
        return (false);
    if (!is_printable(map->obstacle) || !is_printable(map->empty) || !is_printable(map->full))
        return (false);
    map->grid = calloc(map->height, sizeof(char *));
    if (!map->grid)
        return (free(line), false);
    return (true);
}

bool line_check(char *line, int len, char **map)
{
    
}

bool parse_map(FILE *file, t_map *map)
{
    char    *line;
    size_t  cap;
    size_t  len;
    
    len = getline(&line, &cap, file);
    if (len < 8 || !line)
        return (false);
    if (!parse_header(line, len, map))
        return (false);
    cap = 0;
    line = NULL;
    for (int i =0; i < map->height; i++)
    {
        len = getline(&line, &cap, file);
        if (len <= 0 || !line_check(line, len, map))
            return (free_map(), false);
    } 
}