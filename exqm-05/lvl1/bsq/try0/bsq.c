#include "bsq.h"

void    free_map(t_map *m)
{
    int i = 0;
    if (m->grid)
    {
        while (i < m->rows)
        {
            free(m->grid[i]);
            i ++;
        }
        free(m->grid);
    }
    m->grid = NULL;
    return ;
}

bool is_printable(char c)
{
    if (c < ' ' || c > 126)
        return (false);
    return (true);
}

bool parse_header(char *line, long len, t_map *m)
{
    long i;
    long n;

    if (len < 8 || line[len - 1] != '\n')
        return (false);
    if (line[len - 3] != ' ' || line[len - 5] != ' ' || line[len - 7] != ' ')
        return (false);
    m->full = line[len - 3];
    m->obstacle = line[len - 5];
    m->empty = line[len - 7];
    i = 0;
    n = 0;
    while (i < len - 7)
    {
        if (line[i] < '0' || line[i] > '9')
            return (false);
        n = n * 10 + (line[i] - '0');
        if (n > __INT32_MAX__)
            return (false);
        i++;
    }
    if (n <= 0)
        return (false);
    if (!is_printable(m->empty) || !is_printable(m->obstacle) || !is_printable(m->full))
        return (false);
    if (m->empty == m->obstacle || m->empty == m->full || m->obstacle == m->full)
        return (false);
    m->rows = n;
    return (true);
}

bool    checkline(char *line, int len, t_map *m, int i)
{
    long    j;

    if (len < 2 || line[len - 1] != '\n')
        return (0);
    line[len - 1] = '\0';
    len--;
    if (i == 0)
        m->cols = len;
    else if (len != m->cols)
        return (false);
    j = 0;
    while (j < len)
    {
        if (line[j] != m->empty && line[j] != m->obstacle)
            return (false);
        j++;
    }
    return (true);
}

bool parse_map(FILE *file, t_map *m)
{
    char    *line = NULL;
    long    len;
    size_t n;
    int     i;

    len = getline(&line, &n, file);
    if (len <= 0 || !parse_header(line, len, m))
        return (free(line), false);
    m->grid = calloc(m->rows, sizeof(char *));
    if (!m->grid)
        return (free(line), false);
    i = 0;
    line = NULL;
    while (i < m->rows)
    {
        len = getline(&line, &n, file);
        if (len <= 0 || !checkline(line, len, m, i))
            return (free_map(m), free(line), false);
        m->grid[i] = line;
        line = NULL;
        len = 0;
    }
    if (getline(&line, &n, file) != -1)
		return (free(line), free_map(m), 0);
    free(line);
    return (true);
}