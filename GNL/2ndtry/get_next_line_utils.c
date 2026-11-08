/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillichien <chillichien@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:58:52 by chillichien       #+#    #+#             */
/*   Updated: 2025/06/16 18:03:36 by chillichien      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

void	ft_bzero(char *s, int n)
{
	int	count;

	count = 0;
	if (s)
	{
		while (count < n)
		{
			s[count] = 0;
			count++;
		}
	}
}

int	ft_strlen(char *s)
{
	int	count;

	count = 0;
	if (s)
	{
		while (s[count])
			count++;
	}
	return (count);
}

int	where_is_newline(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
		return (-1);
	else
		return (i);
}

void	ft_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	if (src)
	{
		while (src[i] && i < n)
		{
			dest[i] = src[i];
			i++;
		}
	}
}

void	empty_before_newline(char *holder, int index)
{
	char	tmp[BUFFER_SIZE +1];
	int		count;

	count = 0;
	ft_bzero(tmp, BUFFER_SIZE +1);
	ft_strncpy(tmp, holder, BUFFER_SIZE + 1);
	while (count < BUFFER_SIZE + 1)
	{
		holder[count] = 0;
		count++;
	}
	ft_strncpy(holder, &tmp[index + 1], BUFFER_SIZE + 1);
}
