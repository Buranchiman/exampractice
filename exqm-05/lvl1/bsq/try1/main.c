#include "bsq.h"

bool process(FILE *file, t_map *map)
{
    if (!parse_map(file, map))
        return (false);
}

int main(int arc, char **arv)
{
    FILE *file;
    t_map map;

    if (arc < 2)
    {
        if (!process(stdin, &map))
            return (fputs("map error\n", stderr), 1);
        solve(&map);
        return (0);
    }
    for (int i  = 1; i < arc; i++)
    {
        file = fopen(arv[i], "r");
        if (!file)
            return (fputs("map error\n", stderr), 1);
        if (!process(file, &map))
            return (fputs("map error\n", stderr), 1);
        solve(&map);
    }
}