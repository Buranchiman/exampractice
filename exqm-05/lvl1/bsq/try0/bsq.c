#include "bsq.h"

void print_map(t_map *map)
{
	fputs("reached print\n", stdout);
	for (int i = 0; i < map->rows; i++)
	{
		fputs(map->grid[i], stdout);
		fputs("\n", stdout);
	}
}

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

	// fputs("entered header\n", stdout);
    if (len < 8 || line[len - 1] != '\n')
        return (false);
    if (line[len - 3] != ' ' || line[len - 5] != ' ' || line[len - 7] != ' ')
        return (false);
    m->full = line[len - 2];
    m->obstacle = line[len - 4];
    m->empty = line[len - 6];
    i = 0;
    n = 0;
	// fputs("entered lenghh parser check\n", stdout);
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
	// fputs("passed isprint\n", stdout);
    if (m->empty == m->obstacle || m->empty == m->full || m->obstacle == m->full)
        return (false);
	// fputs("passed isdup\n", stdout);
    m->rows = n;
	// fprintf(stdout, "nb rows is %d\n", m->rows);
	// fputs("finished parsed header\n", stdout);
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
        return (fputs("exit because len of line diff\n", stdout), false);
    j = 0;
    while (j < len)
    {
        if (line[j] != m->empty && line[j] != m->obstacle)
            return (fprintf(stdout, "exit at char check because char is %c\n", line[j]), false);
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
	//fputs("entered line check\n", stdout);
    while (i < m->rows)
    {
        len = getline(&line, &n, file);
        if (len <= 0 || !checkline(line, len, m, i))
            return (free_map(m), free(line), false);
        m->grid[i] = line;
        line = NULL;
        n = 0;
		i++;
    }
	//fputs("At the end of parsing map is :", stdout);
	// print_map(m);
    if (getline(&line, &n, file) != -1)
		return (free(line), free_map(m), 0);
    free(line);
    return (true);
}

int min3 (int a, int b, int c)
{
	if (a > b)
		a = b;
	if (a > c)
		a = c;
	return (a);
}

void fill(t_map *map, int side, int bi, int bj)
{
	for (int i = bi - side + 1; i <= bi; i++)
	{
		for (int j = bj - side + 1; j <= bj; j++)
		{
			map->grid[i][j] = map->full;
		}
	}
}

bool solve(t_map *map)
{
	int	i;
	int	j;
	int	*cur;
	int	*prev;
	int *tmp;
	int	best;
	int bi;
	int bj;

	cur = calloc(map->cols + 1, sizeof(int));
	prev = calloc(map->cols + 1, sizeof(int));

	if (!prev || !cur)
		return (free(prev), free(cur), 0);
	best = 0;
	bi = 0;
	bj = 0;
	best = 0;
	i = 0;
	while (i < map->rows)
	{
		j = 1;
		while (j <= map->cols)
		{
			if (map->grid[i][j - 1] == map->obstacle)
				cur[j] = 0;
			else
				cur[j] = min3(cur[j - 1], prev[j], prev[j - 1]) + 1;
			if (cur[j] > best)
			{
				best = cur[j];
				bi = i;
				bj = j - 1;
			}
			j++;
		}
		tmp = prev;
		prev = cur;
		cur = tmp;
		i++;
	}
	free(prev);
	free(cur);
	//fprintf(stdout, "At end of solve, data is best=%d bi=%d bj=%d\n", best, bi, bj);
	if (best > 0)
		fill(map, best, bi, bj);
	return (true);
}
