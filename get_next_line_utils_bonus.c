/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:48:44 by xiaxu             #+#    #+#             */
/*   Updated: 2024/05/25 19:52:11 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_lineList	*ft_lst_first(int fd, t_lineList **lineList)
{
	t_lineList	*first;

	if (!(*lineList))
		*lineList = ft_lst_new_fd(fd);
	if (!(*lineList))
		return (NULL);
	first = *lineList;
	while (first->fd != fd && first->next_linelist)
		first = first->next_linelist;
	if (first->fd != fd)
	{
		first->next_linelist = ft_lst_new_fd(fd);
		first = first->next_linelist;
	}
	return (first);
}

t_bufferList	*ft_lst_new_buffer(void)
{
	t_bufferList	*new;

	new = malloc(sizeof(t_bufferList));
	if (!new)
		return (NULL);
	new->content = malloc(BUFFER_SIZE + 1);
	if (!(new->content))
		return (free(new), NULL);
	(new->content)[0] = '\0';
	new->next_bufferlist = 0;
	return (new);
}

t_lineList	*ft_lst_new_fd(int fd)
{
	t_lineList	*new;

	new = malloc(sizeof(t_lineList));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->buffer = ft_lst_new_buffer();
	if (!(new->buffer))
		return (free(new), NULL);
	new->next_linelist = 0;
	return (new);
}

size_t	count_memory(t_bufferList *current)
{
	size_t	memory;
	size_t	i;

	memory = 1;
	while (current)
	{
		i = 0;
		while ((current->content)[i])
		{
			memory++;
			i++;
			if ((current->content)[i - 1] == '\n')
				break ;
		}
		if (i > 0 && (current->content)[i - 1] == '\n')
		{
			i++;
			break ;
		}
		current = current->next_bufferlist;
	}
	return (memory);
}

int	ft_punct(char *content)
{
	size_t	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
