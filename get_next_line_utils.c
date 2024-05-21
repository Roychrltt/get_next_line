/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:22:51 by xiaxu             #+#    #+#             */
/*   Updated: 2024/05/21 21:17:44 by xiaxu            ###   ########.fr       */
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

static void	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);
	ft_strcpy(res, s1);
	ft_strcpy((res + len1), s2);
	res[len1 + len2] = 0;
	return (res);
}

char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*sub;
	size_t	i;

	if (start)
		start++;
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
