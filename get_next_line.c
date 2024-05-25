/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:26:00 by xiaxu             #+#    #+#             */
/*   Updated: 2024/05/25 15:08:56 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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


	while ((bytes_read = read(fd, cur, BUFFER_SIZE)) > 0)
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
	}
}

char	*get_next_line(int fd)
{
	char		*cur;
	char		*readed;
	static char	remnant[BUFFER_SIZE + 1];

	cur = malloc(BUFFER_SIZE + 1);
	if (!cur)
		return (NULL);
	readed = malloc(BUFFER_SIZE + 1);
	if (!readed)
		return (free(cur), NULL);
	if (check_remnant(remnant, readed))
	{
		free(cur);
		return (readed);
	}
	read_file(fd, cur, &readed, remnant);
	free(cur);
	if (ft_strlen(readed) == 0)
	{
		free(readed);
		return (NULL);
	}
	return (readed);
}


int main()
{
	int fd = open("readlinetest.txt", O_RDONLY);
	printf("first line readed: %s", get_next_line(fd));
	printf("first line readed: %s", get_next_line(fd));
	printf("first line readed: %s", get_next_line(fd));
}

