/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:18:16 by xiaxu             #+#    #+#             */
/*   Updated: 2024/05/26 15:18:18 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_fdList	*ft_lst_first(int fd, t_fdList **fdList)
{
	t_fdList	*first;

	if (!(*fdList))
		*fdList = ft_lst_new_fd(fd);
	if (!(*fdList))
		return (NULL);
	first = *fdList;
	while (first->fd != fd && first->next_fdlist)
		first = first->next_fdlist;
	if (first->fd != fd)
	{
		first->next_fdlist = ft_lst_new_fd(fd);
		first = first->next_fdlist;
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

t_fdList	*ft_lst_new_fd(int fd)
{
	t_fdList	*new;

	new = malloc(sizeof(t_fdList));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->buffer = ft_lst_new_buffer();
	if (!(new->buffer))
		return (free(new), NULL);
	new->next_fdlist = 0;
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

int	ft_strchr(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
