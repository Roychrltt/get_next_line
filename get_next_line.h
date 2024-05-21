/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:15:33 by xiaxu             #+#    #+#             */
/*   Updated: 2024/05/21 21:21:06 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h> 
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

size_t	ft_strlen(const char *s);
size_t	ft_strchr(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, size_t start, size_t len);

#endif
