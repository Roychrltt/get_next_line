/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:17:14 by xiaxu             #+#    #+#             */
/*   Updated: 2024/05/26 15:18:00 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_bufferList
{
	char					*content;
	struct s_bufferList		*next_bufferlist;
}			t_bufferList;

typedef struct s_fdList
{
	int						fd;
	t_bufferList			*buffer;
	struct s_fdList			*next_fdlist;
}			t_fdList;

char			*get_next_line(int fd);
t_bufferList	*ft_lst_new_buffer(void);
t_fdList		*ft_lst_new_fd(int fd);
t_fdList		*ft_lst_first(int fd, t_fdList **fdList);
int				ft_strchr(char *s);
size_t			count_memory(t_bufferList *current);

#endif
