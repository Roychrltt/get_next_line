/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:26:00 by xiaxu             #+#    #+#             */
/*   Updated: 2024/05/22 10:17:29 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*strinit(void)
{
	char	*s;

	s = malloc(BUFFER_SIZE + 1);
	if (!s)
		return (NULL);
	s[0] = 0;
	return (s);
}

static int	check_remnant(char **remnant, char **readed)
{
	size_t	pos;
	size_t	len;
	char	*temp;

	if (*remnant)
	{
		pos = ft_strchr(*remnant);
		len = ft_strlen(*remnant);
		if (pos < len)
		{
			ft_strlcpy(*readed, *remnant, pos + 1);
			temp = ft_substr(*remnant, pos + 1, len - pos - 1);
			free(*remnant);
			*remnant = temp;
			return (1);
		}
		else
		{
			ft_strlcpy(*readed, *remnant, len);
			free(*remnant);
			*remnant = NULL;
		}
	}
	return (0);
}

static void	update_readed(char **readed, char *new)
{
	char	*temp;

	if (!*readed)
		*readed = new;
	else
	{
		temp = ft_strjoin(*readed, new);
		free(*readed);
		*readed = temp;
		free(new);
	}
}

void	read_file(int fd, char *cur, char *readed, char **remnant)
{
	char	*new;
	size_t	bytes_read;

	bytes_read = read(fd, cur, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		cur[bytes_read] = 0;
		if (ft_strchr(cur) < BUFFER_SIZE)
		{
			new = ft_substr(cur, 0, ft_strchr(cur) + 1);
			update_readed(&readed, new);
			free(*remnant);
			*remnant = ft_substr(cur, ft_strchr(cur) + 1, BUFFER_SIZE);
			break ;
		}
		else
			update_readed(&readed, cur);
	}
	free(cur);
}

char	*get_next_line(int fd)
{
	char		*cur;
	char		*readed;
	static char	*remnant = NULL;

	cur = strinit();
	readed = strinit();
	if (!cur || !readed)
	{
		free(cur);
		free(readed);
		return (NULL);
	}
	if (check_remnant(&remnant, &readed))
	{
		free(cur);
		return (readed);
	}
	read_file(fd, cur, readed, &remnant);
	if (ft_strlen(readed) == 0)
	{
		free(readed);
		return (NULL);
	}
	return (readed);
}
#include <stdio.h>

int main()
{
	int fd = open("readlinetest.txt", O_RDONLY);
	char *s = get_next_line(fd);
	printf("Line read: %s", s);
	free(s);
	char *s1 = get_next_line(fd);
	printf("Line read: %s", s1);
	free(s1);
}
