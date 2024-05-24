/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:26:00 by xiaxu             #+#    #+#             */
/*   Updated: 2024/05/24 19:13:30 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
//check if *remnant is well terminated
static int	check_remnant(char *remnant, char *readed)
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
			remnant += pos + 1;
			return (1);
		}
		else
			ft_strlcpy(readed, remnant, len);
	}
	return (0);
}

static void	update_readed(char **readed, char **new)
{
	char	*temp;

	if (ft_strlen(*readed) == 0)
		ft_strlcpy(*readed, *new, ft_strlen(*new));
	else
	{
		temp = malloc(ft_strlen(*readed) + ft_strlen(*new) + 1);
		if (!temp)
			return ;
		ft_strlcpy(temp, *readed, ft_strlen(*readed));
		ft_strlcpy(temp + ft_strlen(*readed), *new, ft_strlen(*new));
		*readed = temp;
		free(temp);
	}
}

void	read_file(int fd, char *cur, char *readed, char *remnant)
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
			update_readed(&readed, &new);
			remnant += pos + 1;
			break ;
		}
		else
			update_readed(&readed, &cur);
	}
	free(new);
	free(cur);
}

char	*get_next_line(int fd)
{
	char		*cur;
	char		*readed;
	static char	remnant[BUFFER_SIZE + 1];

	cur = malloc(BUFFER_SIZE + 1);
	readed = malloc(BUFFER_SIZE + 1);
	remnant[0] = 0;
	if (!cur || !readed)
		return (NULL);
	cur[0] = 0;
	readed[0] = 0;
	if (check_remnant(remnant, readed))
	{
		free(cur);
		return (readed);
	}
	read_file(fd, cur, readed, remnant);
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
	printf("Line read: %s\n", s);
	free(s);
	char *s1 = get_next_line(fd);
	printf("Line read: %s", s1);
	free(s1);
}

