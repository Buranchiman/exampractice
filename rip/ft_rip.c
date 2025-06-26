#include <stdio.h>

int     ft_strlen(char *s)
{
        int     i = 0;

        if (s)
        {
                while (s[i])
                        i++;
        }
        return (i);
}

void	build_base(char *src, char *dest)
{
	int	i = 0;
	
	while (src[i] && src[i] != '(')
	{
		if (src[i] == ')')
			dest[i] = ' ';
		i++;
	}
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	i --;
	while (i >= 0 && src[i] != ')')
	{
                if (src[i] == '(')
                        dest[i] = ' ';
                i--;
        }
}

int	moves_needed(char *s)
{
	int	i = 0;
	int	open_count = 0;
	int	close_count = 0;
	int	absolute;

	while (s[i])
	{
		if (s[i] == '(')
			open_count++;
		if (s[i] == ')')
			close_count ++;
		i++;
	}
	absolute = open_count - close_count;
	if (absolute < 0)
		absolute = -absolute;
	 return (absolute);
}

void	ft_rip_it(char *og, char *dup, int index, int curr, int max, int open)
{
	if (!dup[index] && curr == max && !open)
	{
		printf("%s\n", dup);
		return ;
	}
	if (og[index] == ' ')
	{
		dup[index] = ' ';
		ft_rip_it(og, dup, index + 1, curr, max, open);
	}
	else if (og[index] == '(')
	{
		dup[index] = '(';
		ft_rip_it(og, dup, index + 1, curr, max, open + 1);
		dup[index] = ' ';
		ft_rip_it(og, dup, index + 1, curr + 1, max, open);
	}
	else if (og[index] == ')')
	{
		if (open)
		{
			dup[index] = ')';
                	ft_rip_it(og, dup, index + 1, curr, max, open -1);
		}
		dup[index] = ' ';
                ft_rip_it(og, dup, index + 1, curr + 1, max, open);
	}
	return ;
}

	

int	main(int arc, char **arv)
{
	if (arc != 2 || !ft_strlen(arv[1]))
		return (1);
	char	s[ft_strlen(arv[1] + 1)];
	char	dup[ft_strlen(arv[1] + 1)];
	int	i = 0;

	while (i < ft_strlen(arv[1]) + 1)
	{
		s[i] = 0;
		dup[i] = 0;
		i++;
	}
	build_base(arv[1], s);
	//build_base(arv[1], dup);
	int	moves = moves_needed(s);
	//printf("after clean is %sand needs %d moves to be solved\n", s, moves);
	ft_rip_it(s, dup, 0, 0, moves, 0);
	return (0);
}
