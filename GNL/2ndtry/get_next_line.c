/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillichien <chillichien@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:53:40 by chillichien       #+#    #+#             */
/*   Updated: 2025/06/16 18:05:50 by chillichien      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

char	*ft_calloc(size_t size)
{
	char	*stock;
	size_t	count;

	stock = malloc(sizeof(char) * size + 1);
	if (!stock)
		return (NULL);
	count = 0;
	while (count < size + 1)
	{
		stock[count] = 0;
		count++;
	}
	return (stock);
}

static bool	get_line(char **line, char *holder)
{
	int	i;

	i = 0;
	if (ft_strlen(holder) == 0)
		return (true);
	if (holder[i])
	{
		while (holder[i] && holder[i] != '\n')
			i++;
	}
	*line = ft_calloc(i + 1);
	if (!line)
		return (false);
	ft_strncpy(*line, holder, i + 1);
	if (!holder[i])
		ft_bzero(holder, BUFFER_SIZE + 1);
	else
		empty_before_newline(holder, i);
	return (true);
}

static bool	ft_strjoin(char **s1, char *s2)
{
	int		len1;
	int		len2;
	char	*joined;

	len1 = ft_strlen(*s1);
	len2 = ft_strlen(s2);
	joined = ft_calloc(len1 + len2);
	if (!joined)
	{
		if (s1)
			free(s1);
		return (false);
	}
	ft_strncpy(joined, *s1, len1);
	ft_strncpy(&joined[len1], s2, len2);
	if (*s1)
		free(*s1);
	*s1 = joined;
	return (true);
}

static bool	read_file(char **line, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		stock;

	stock = 1;
	while (stock > 0)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		stock = read(fd, buffer, BUFFER_SIZE);
		if (stock < 1)
		{
			if (*line)
				free(*line);
			return (false);
		}
		if (!ft_strjoin(line, buffer))
			return (false);
		if (where_is_newline(*line) != -1)
			return (true);
	}
	return (true);
}

char	*get_next_line(int fd)
{
	static char	holder[BUFFER_SIZE + 1];
	char		*line;
	int			count;

	if (fd < 0)
		return (NULL);
	line = NULL;
	if (!get_line(&line, holder))
		return (NULL);
	if (where_is_newline(line) != -1)
		return (line);
	if (!read_file(&line, fd))
		return (NULL);
	if (where_is_newline(line) != -1)
	{
		ft_bzero(holder, BUFFER_SIZE + 1);
		count = where_is_newline(line) + 1;
		ft_strncpy(holder, &line[count], BUFFER_SIZE + 1);
		while (line[count])
		{
			count++;
			line[count - 1] = 0;
		}
	}
	return (line);
}

/*int	main(int argc, char **argv)
{
	int	fd;
	char	*buffer;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	buffer = get_next_line(fd);
	printf("line is %s", buffer);
	free(buffer);
	buffer = get_next_line(fd);
	printf("line is %s", buffer);
        free(buffer);
	while (buffer)
	{
		printf("%s", buffer);
		free(buffer);
		buffer = get_next_line(fd);
	}
	return (0);
}*/
