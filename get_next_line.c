/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:26:00 by xiaxu             #+#    #+#             */
/*   Updated: 2024/05/21 13:21:37 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

char	*get_next_line(int fd)
{
	int			i;
	char		*readed;
	static char	*rem;

	if (!get_rem(&rem, fd))
		reutrn (NULL);
	return (readed);
}
