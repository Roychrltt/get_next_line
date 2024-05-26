/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:26:00 by xiaxu             #+#    #+#             */
/*   Updated: 2024/05/26 14:38:54 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_remnant(char *remnant, char *readed)
{
	size_t	pos;
	size_t	len;

	if (*remnant)
	{
		pos = ft_strchr(remnant);
		len = ft_strlen(remnant);
		if (pos < len)
		{
			ft_strlcpy(readed, remnant, pos + 1);
			ft_strlcpy(remnant, remnant + pos + 1, len - pos - 1);
			return (1);
		}
		else
			ft_strlcpy(readed, remnant, len);
	}
	return (0);
}

void	update_readed(char **readed, char *new)
{
	char	*temp;
	size_t	readlen;
	size_t	newlen;

	readlen = ft_strlen(*readed);
	newlen = ft_strlen(new);
	if (readlen == 0)
		ft_strlcpy(*readed, new, newlen);
	else
	{
		temp = malloc(readlen + newlen + 1);
		if (!temp)
			return ;
		ft_strlcpy(temp, *readed, readlen);
		ft_strlcpy(temp + readlen, new, newlen);
		free(*readed);
		*readed = temp;
	}
}

void	read_file(int fd, char *cur, char **readed, char *remnant)
{
	char	*new;
	size_t	bytes_read;
	size_t	pos;

	bytes_read = read(fd, cur, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		cur[bytes_read] = 0;
		pos = ft_strchr(cur);
		if (pos < bytes_read)
		{
			new = ft_substr(cur, 0, pos + 1);
			if (!new)
				return ;
			update_readed(readed, new);
			free(new);
			ft_strlcpy(remnant, cur + pos + 1, ft_strlen(cur) - pos);
			break ;
		}
		else
			update_readed(readed, cur);
		bytes_read = read(fd, cur, BUFFER_SIZE);
	}
	if (bytes_read == 0)
		remnant[0] = 0;
}

char	*get_next_line(int fd)
{
	char		*cur;
	char		*readed;
	static char	remnant[BUFFER_SIZE + 1];

	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	cur = malloc(BUFFER_SIZE + 1);
	if (!cur)
		return (NULL);
	cur[0] = 0;
	readed = malloc(BUFFER_SIZE + 1);
	if (!readed)
		return (free(cur), NULL);
	readed[0] = 0;
	if (check_remnant(remnant, readed))
		return (free(cur), readed);
	read_file(fd, cur, &readed, remnant);
	free(cur);
	if (ft_strlen(readed) == 0)
		return (free(readed), NULL);
	return (readed);
}
/*
#include <stdio.h>
int main()
{
int fd = open("test.txt", O_RDONLY);
printf("Line readed: %s", get_next_line(fd));
printf("Line readed: %s", get_next_line(fd));
printf("Line readed: %s", get_next_line(fd));
printf("Line readed: %s", get_next_line(fd));
printf("Line readed: %s", get_next_line(fd));
printf("Line readed: %s", get_next_line(fd));
printf("Line readed: %s", get_next_line(fd));
printf("Line readed: %s", get_next_line(fd));
printf("Line readed: %s", get_next_line(fd));
printf("Line readed: %s", get_next_line(fd));
printf("Line readed: %s", get_next_line(fd));
printf("Line readed: %s", get_next_line(fd));
printf("Line readed: %s", get_next_line(fd));
close(fd);
}*/
