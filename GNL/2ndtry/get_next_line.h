/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillichien <chillichien@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:02:53 by chillichien       #+#    #+#             */
/*   Updated: 2025/06/16 18:04:16 by chillichien      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void	ft_bzero(char *s, int n);
int		ft_strlen(char *s);
int		where_is_newline(char *s);
void	ft_strncpy(char *dest, char *src, int n);
void	empty_before_newline(char *holder, int index);
char	*get_next_line(int fd);

#endif
