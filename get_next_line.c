/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:26:00 by xiaxu             #+#    #+#             */
/*   Updated: 2024/05/21 21:20:36 by xiaxu            ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	size_t		pos;
	char		*curline;
	char		*readed;
	char		*new;
	static char	*remnant = NULL;

	curline = strinit();
	readed = strinit();
	while ((read(fd, curline, BUFFER_SIZE)) > 0)
	{
		pos = ft_strchr(curline);
		new = ft_substr(curline, 0, pos + 1);
		if (readed != NULL)
			readed = ft_strjoin(readed, new);
		else
			readed = new;
		if (pos < BUFFER_SIZE)
		{
			if (remnant != NULL)
				readed = ft_strjoin(remnant, readed);
			remnant = ft_substr(curline, pos, BUFFER_SIZE);
			return (readed);
		}
	}
	return (readed);
}
/*
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
}*/
