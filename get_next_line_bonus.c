/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:48:28 by xiaxu             #+#    #+#             */
/*   Updated: 2024/05/25 19:52:01 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_read_fd(int fd, t_bufferList *first, t_bufferList *c_buffer)
{
	int	isread;

	isread = 0;
	if (first && ft_punct(first->content))
		return (1);
	else if (first && (first->content[0]))
	{
		first->next_bufferlist = ft_lst_new_buffer();
		c_buffer = first->next_bufferlist;
	}
	while (1)
	{
		isread = read(fd, c_buffer->content, BUFFER_SIZE);
		if (isread <= 0)
			break ;
		(c_buffer->content)[isread] = '\0';
		if (ft_punct(c_buffer->content))
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
	line[i] = '\0';
	return (line);
}

static void	ft_clean_buffers(t_bufferList *c_buffer, t_lineList *c_linelist)
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
		c_linelist->buffer = next;
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

t_lineList	*ft_clean_fd_list(t_lineList *s_list, t_lineList *c_linelist)
{
	t_lineList	*tmp;

	if (!((c_linelist->buffer->content)[0]))
	{
		free(c_linelist->buffer->content);
		free(c_linelist->buffer);
		if (s_list == c_linelist)
			s_list = s_list->next_linelist;
		else
		{
			tmp = s_list;
			while (tmp->next_linelist && tmp->next_linelist != c_linelist)
				tmp = tmp->next_linelist;
			if (tmp->next_linelist)
				tmp->next_linelist = tmp->next_linelist->next_linelist;
		}
		free(c_linelist);
	}
	return (s_list);
}

char	*get_next_line(int fd)
{
	char				*s;
	static t_lineList	*static_linelist;
	t_lineList			*c_linelist;
	t_bufferList		*c_bufferlist;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	c_linelist = ft_lst_first(fd, &static_linelist);
	if (!c_linelist)
		return (NULL);
	c_bufferlist = c_linelist->buffer;
	if (ft_read_fd(fd, c_bufferlist, c_bufferlist))
		s = ft_get(c_bufferlist);
	else
		s = NULL;
	ft_clean_buffers(c_bufferlist, c_linelist);
	static_linelist = ft_clean_fd_list(static_linelist, c_linelist);
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
