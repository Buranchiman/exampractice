#include <unistd.h>
#include <string.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}

int	ft_cd(char **argv, int i)
{
	int	status;

	status = 0;
	if (i != 2)
		return (ft_putstr_fd("error: cd: bad arguments\n", 2), 1);
	else
	{
		status = chdir(argv[1]);
		if (status)
		{
			ft_putstr_fd("error: cd: cannot change directory ", 2);
			ft_putstr_fd(argv[1], 2);
			return (ft_putstr_fd("\n", 2), status);
		}
	}
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	if (argc > 1)
	{
		while (argv)
		{
			argv += i;
			i = 0;
			while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
				i++;
			if (argv[i] && !strcmp(*argv, "cd"))
				status = ft_cd(argv, i);
			else if (i)
				status = ft_exec(argv, envp, i);
			i++;
		}
	}
}
