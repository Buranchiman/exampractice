#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	ft_strindex(char *s, char c)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] && s[i] != c)
			i++;
		if (s[i])
			return	(i);
		else
			return (-1);
	}
	return (-1);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
		return (i);
	}
}

void	ft_bzero(char *s, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		s[i] = '\0';
		i++;
	}
	//printf("finished bzero\n");
}

char	*ft_calloc(int n)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char) * n + 1);
	if (!ret)
		return (ret);
	i = 0;
	while (i <= n)
	{
		ret[i] = '\0';
		i++;
	}
	return (ret);
}

int	ft_strncopy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (0);
}

int	get_line(char **line, char *holder)
{
	int	i;

	i = 0;
	while (holder[i] && holder[i] != '\n')
		i++;
	if (holder[i])
	{
		*line = ft_calloc(i);
		if (!(*line))
			return (-1);
		ft_strncopy(*line, holder, i);
		//printf("line is %s", *line);
		if (!holder[i + 1])
		{
			ft_bzero(holder, BUFFER_SIZE + 1);
			return (1);
		}
		ft_strncopy(holder, &holder[i], BUFFER_SIZE + 1);
		return (1);
	}
	else
	{
		ft_strncopy(*line, holder, i);
		ft_bzero(holder, BUFFER_SIZE + 1);
		return (0);
	}
}

int	ft_strjoin(char **s1, char *s2)
{
	int		i;
	char	*joined;
	int		j;

	joined = ft_calloc(ft_strlen(*s1) + ft_strlen(s2) + 1);
	if (!joined)
		return (-1);
	i = 0;
	if (*s1)
	{
		while ((*s1)[i])
		{
			joined[i] = (*s1)[i];
		}
	}
	j = 0;
	while (s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	if (*s1)
		free(*s1);
	//printf("joined is %s\n", joined);
	*s1 = joined;
	return (0);
}

int	ft_reading(int	fd, char **line)
{
	char	buffer[BUFFER_SIZE + 1];
	int		code;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	code = read(fd, buffer, BUFFER_SIZE);
	while (code > 0 && ft_strindex(*line, '\n') == -1)
	{
		if (ft_strjoin(line, buffer) == -1)
		{
			free(*line);
			return (-1);
		}
		//printf("line is %s", *line);
		//printf("PATATE\n");
		ft_bzero(buffer, BUFFER_SIZE + 1);
		code = read(fd, buffer, BUFFER_SIZE);
	}
	if (code == -1)
	{
		if (*line)
			free(*line);
		return (-1);
	}
	return (0);
}

int	ft_strtrim(char **s, int index)
{
	int		i;
	char	*trimmed;

//	printf("entered trim\n");
	while((*s)[index + i])
		i++;
	trimmed = ft_calloc(ft_strlen(*s) - i);
	if (!trimmed)
		return (-1);
	i = 0;
	while (i < index)
	{
		trimmed[i] = (*s)[i];
		i++;
	}
	free(*s);
	*s = trimmed;
	return (0);
}

char	*get_next_line(int fd)
{
	static char	holder[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0)
		return (NULL);
	line = NULL;
	if (get_line(&line, holder) != 0)
		return (line);
	if (ft_reading(fd, &line) == -1)
		return (NULL);
	if (ft_strindex(line, '\n') != -1)
	{
		ft_strncopy(holder, &line[ft_strindex(line, '\n') + 1], BUFFER_SIZE + 1);
		if (ft_strtrim(&line, ft_strindex(line, '\n') + 1) == -1)
		{
			free(line);
			return (NULL);
		}
		printf("rest is %s\n", holder);
	}
	return (line);
}

#include <stdio.h>

int	main(int argc, char **argv)
{
	char	*ret;
	int		fd;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	ret = get_next_line(fd);
	while (ret)
	{
		//printf("%s", ret);
		free(ret);
		ret = get_next_line(fd);
	}
	return (0);
}
