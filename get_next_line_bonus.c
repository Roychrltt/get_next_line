/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:16:08 by xiaxu             #+#    #+#             */
/*   Updated: 2024/05/26 15:16:51 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_read_fd(int fd, t_bufferList *first, t_bufferList *c_buffer)
{
	int	bytes_read;

	bytes_read = 0;
	if (first && ft_strchr(first->content))
		return (1);
	else if (first && (first->content[0]))
	{
		first->next_bufferlist = ft_lst_new_buffer();
		c_buffer = first->next_bufferlist;
	}
	while (1)
	{
		bytes_read = read(fd, c_buffer->content, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		(c_buffer->content)[bytes_read] = '\0';
		if (ft_strchr(c_buffer->content))
			break ;
		c_buffer->next_bufferlist = ft_lst_new_buffer();
		c_buffer = c_buffer->next_bufferlist;
	}
	if (!(first->content[0]))
		return (0);
	return (1);
}

static char	*ft_get(t_bufferList *current_buffer)
{
	char			*line;
	size_t			i;
	size_t			j;

	line = malloc(count_memory(current_buffer));
	if (!line)
		return (NULL);
	i = 0;
	while (current_buffer && current_buffer->content)
	{
		j = 0;
		while ((current_buffer->content)[j] && (i == 0 || line[i - 1] != '\n'))
			line[i++] = (current_buffer->content)[j++];
		current_buffer = current_buffer->next_bufferlist;
	}
	line[i] = 0;
	return (line);
}

static void	ft_clean_buffers(t_bufferList *c_buffer, t_fdList *c_fdlist)
{
	size_t					i;
	size_t					j;
	t_bufferList			*next;

	while (c_buffer->next_bufferlist)
	{
		next = c_buffer->next_bufferlist;
		free(c_buffer->content);
		free(c_buffer);
		c_buffer = next;
		c_fdlist->buffer = next;
	}
	i = 0;
	while ((c_buffer->content)[i])
	{
		i++;
		if ((c_buffer->content)[i - 1] == '\n')
			break ;
	}
	j = 0;
	while ((c_buffer->content)[i])
		(c_buffer->content)[j++] = (c_buffer->content)[i++];
	(c_buffer->content)[j] = '\0';
}

t_fdList	*ft_clean_fd_list(t_fdList *s_list, t_fdList *c_fdlist)
{
	t_fdList	*tmp;

	if (!((c_fdlist->buffer->content)[0]))
	{
		free(c_fdlist->buffer->content);
		free(c_fdlist->buffer);
		if (s_list == c_fdlist)
			s_list = s_list->next_fdlist;
		else
		{
			tmp = s_list;
			while (tmp->next_fdlist && tmp->next_fdlist != c_fdlist)
				tmp = tmp->next_fdlist;
			if (tmp->next_fdlist)
				tmp->next_fdlist = tmp->next_fdlist->next_fdlist;
		}
		free(c_fdlist);
	}
	return (s_list);
}

char	*get_next_line(int fd)
{
	char				*s;
	static t_fdList		*static_fdlist;
	t_fdList			*c_fdlist;
	t_bufferList		*c_bufferlist;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	c_fdlist = ft_lst_first(fd, &static_fdlist);
	if (!c_fdlist)
		return (NULL);
	c_bufferlist = c_fdlist->buffer;
	if (ft_read_fd(fd, c_bufferlist, c_bufferlist))
		s = ft_get(c_bufferlist);
	else
		s = NULL;
	ft_clean_buffers(c_bufferlist, c_fdlist);
	static_fdlist = ft_clean_fd_list(static_fdlist, c_fdlist);
	return (s);
}
/*
int		main(void)
{
	int	fd;
	char*s = NULL;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		printf("%s", s);
	}
	return (0);
}*/
