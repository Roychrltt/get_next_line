/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:48:16 by xiaxu             #+#    #+#             */
/*   Updated: 2024/05/25 19:49:45 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_bufferList
{
	char					*content;
	struct s_bufferList		*next_bufferlist;
}			t_bufferList;

typedef struct s_lineList
{
	int						fd;
	t_bufferList			*buffer;
	struct s_lineList		*next_linelist;
}			t_lineList;

char			*get_next_line(int fd);
t_bufferList	*ft_lst_new_buffer(void);
t_lineList		*ft_lst_new_fd(int fd);
t_lineList		*ft_lst_first(int fd, t_lineList **lineList);
int				ft_punct(char *content);
size_t			count_memory(t_bufferList *current);

#endif
