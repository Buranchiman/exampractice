#include  <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *s)
{
	int	i = 0;

	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}

char	*sort_string(char *s)
{
	int	i = 0;
	int	tries = 0;
	int	len = ft_strlen(s);
	char	tmp;

	while (tries < len)
	{
		i = 0;
		while (s[i + 1])
		{
			if (s[i] > s[i + 1])
			{
				tmp = s[i];
				s[i] = s[i + 1];
				s[i + 1] = tmp;
			}
			i++;
		}
		tries ++;
	}
	return (s);
}

void	ft_permutations(char *sorted, char *perm, int *used, int depth, int len)
{
	int	i = 0;

	if (depth == len)
	{
		printf("%s\n", perm);
		return ;
	}
	while (i < len)
	{
		//printf("i is %d\n", i);
		if (used[i])
		{
			i++;
			continue;
		}
		used[i] = 1;
		perm[depth] = sorted[i];
		ft_permutations(sorted, perm, used, depth + 1, len);
		used[i] = 0;
		i++;
	}
}

int	main(int arc, char **arv)
{
	char	*s;
	int	len = ft_strlen(arv[1]);
	int	*used;
	char	*perm;
	if (arc != 2)
		return (1);
	s = sort_string(arv[1]);
	//printf("sorted string is %s\n", s);
	used = calloc(len, sizeof(int));
	if (!used)
		return (1);
	perm = calloc(len + 1, sizeof(char));
	if (!perm)
		return (free(used), 1);
	ft_permutations(s, perm, used, 0, len);
	free(used);
	free(perm);
	return (0);
}
