/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:16:08 by xiaxu             #+#    #+#             */
/*   Updated: 2024/05/26 15:39:28 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_read_fd(int fd, t_bufferList *first, t_bufferList *cur_buffer)
{
	int	bytes_read;

	bytes_read = 0;
	if (first && ft_strchr(first->content))
		return (1);
	else if (first && (first->content[0]))
	{
		first->next_bufferlist = ft_lst_new_buffer();
		cur_buffer = first->next_bufferlist;
	}
	while (1)
	{
		bytes_read = read(fd, cur_buffer->content, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		(cur_buffer->content)[bytes_read] = 0;
		if (ft_strchr(cur_buffer->content))
			break ;
		cur_buffer->next_bufferlist = ft_lst_new_buffer();
		cur_buffer = cur_buffer->next_bufferlist;
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

	line = malloc(buffer_length(current_buffer));
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

//clean buffer and save the remnant
static void	ft_clean_buffers(t_bufferList *cur_buffer, t_fdList *cur_fdlist)
{
	size_t					i;
	size_t					j;
	t_bufferList			*next;

	while (cur_buffer->next_bufferlist)
	{
		next = cur_buffer->next_bufferlist;
		free(cur_buffer->content);
		free(cur_buffer);
		cur_buffer = next;
		cur_fdlist->buffer = next;
	}
	i = 0;
	while ((cur_buffer->content)[i])
	{
		i++;
		if ((cur_buffer->content)[i - 1] == '\n')
			break ;
	}
	j = 0;
	while ((cur_buffer->content)[i])
		(cur_buffer->content)[j++] = (cur_buffer->content)[i++];
	(cur_buffer->content)[j] = 0;
}

t_fdList	*ft_clean_fd_list(t_fdList *s_list, t_fdList *cur_fdlist)
{
	t_fdList	*tmp;

	if (!((cur_fdlist->buffer->content)[0]))
	{
		free(cur_fdlist->buffer->content);
		free(cur_fdlist->buffer);
		if (s_list == cur_fdlist)
			s_list = s_list->next_fdlist;
		else
		{
			tmp = s_list;
			while (tmp->next_fdlist && tmp->next_fdlist != cur_fdlist)
				tmp = tmp->next_fdlist;
			if (tmp->next_fdlist)
				tmp->next_fdlist = tmp->next_fdlist->next_fdlist;
		}
		free(cur_fdlist);
	}
	return (s_list);
}

char	*get_next_line(int fd)
{
	char				*readed;
	static t_fdList		*staticur_fdlist;
	t_fdList			*cur_fdlist;
	t_bufferList		*cur_bufferlist;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	cur_fdlist = ft_lst_first(fd, &staticur_fdlist);
	if (!cur_fdlist)
		return (NULL);
	cur_bufferlist = cur_fdlist->buffer;
	if (ft_read_fd(fd, cur_bufferlist, cur_bufferlist))
		readed = ft_get(cur_bufferlist);
	else
		readed = NULL;
	ft_clean_buffers(cur_bufferlist, cur_fdlist);
	staticur_fdlist = ft_clean_fd_list(staticur_fdlist, cur_fdlist);
	return (readed);
}
