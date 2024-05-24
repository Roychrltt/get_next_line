/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:22:51 by xiaxu             #+#    #+#             */
/*   Updated: 2024/05/24 20:23:17 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strchr(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

void	ft_strlcpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
}

void	ft_memcpy(char *dst, char *src)
{
	size_t		i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
}

char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*sub;
	size_t	i;

	i = ft_strlen(s + start);
	if (i > len)
		i = len;
	sub = malloc(i + 1);
	if (!sub)
		return (NULL);
	sub[i] = 0;
	while (i--)
		sub[i] = s[start + i];
	return (sub);
}
