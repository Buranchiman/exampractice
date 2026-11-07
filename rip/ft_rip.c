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

/*int	moves_needed(char *s)
{
	int	i = 0;
	int	count = 0;
	//int	close_count = 0;
	//int	absolute;
	int	opened = 0;

	while (s[i])
	{
		if (s[i] == '(' && !opened)
			opened = 1;
		else if (s[i] == '(' && opened)
			count++;
		if (s[i] == ')' && opened)
			opened = 0;
		else if (s[i] == ')' && !opened)
			count ++;
		i++;
	}
	//absolute = open_count - close_count;
	//if (absolute < 0)
	//	absolute = -absolute;
	 return (count);
}*/

void count_min_removals(const char *str, int *left_rem, int *right_rem) {
    *left_rem = 0;
    *right_rem = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == '(') {
            (*left_rem)++;
        } else if (str[i] == ')') {
            if (*left_rem > 0)
                (*left_rem)--;
            else
                (*right_rem)++;
        }
    }
}

void	ft_rip_it(char *og, char *dup, int index, int left_rem, int right_rem , int open)
{
	if (!dup[index] && !left_rem && !right_rem && !open)
	{
		printf("%s\n", dup);
		return ;
	}
	if (og[index] == ' ')
	{
		dup[index] = ' ';
		ft_rip_it(og, dup, index + 1, left_rem, right_rem, open);
	}
	else if (og[index] == '(')
	{
		dup[index] = '(';
		ft_rip_it(og, dup, index + 1, left_rem, right_rem, open + 1);
		dup[index] = ' ';
		ft_rip_it(og, dup, index + 1, left_rem - 1, right_rem, open);
	}
	else if (og[index] == ')')
	{
		if (open)
		{
			dup[index] = ')';
                	ft_rip_it(og, dup, index + 1, left_rem, right_rem, open -1);
		}
		dup[index] = ' ';
                ft_rip_it(og, dup, index + 1, left_rem, right_rem - 1, open);
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
	int	left_rem = 0;
       	int	right_rem = 0;
	count_min_removals(s, &left_rem, &right_rem);
	//printf("after clean is %sand needs %d moves to be solved\n", s, moves);
	ft_rip_it(s, dup, 0, left_rem, right_rem, 0);
	return (0);
}
