/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:07:12 by xabaudhu          #+#    #+#             */
/*   Updated: 2023/12/08 23:40:01 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup_chr(char *s, size_t *len, size_t *check)
{
	char	*dup;
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	dup = malloc(sizeof(*dup) * (i + 2));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		dup[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		dup[i] = s[i];
		*check = ++i;
	}
	else
		*check = 0;
	*len += i;
	dup[i] = '\0';
	return (dup);
}

char	*ft_memcpy_ret(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin_chr_free_s1(char *s1, char *s2, size_t *len, size_t *check)
{
	size_t	i;
	char	*join;

	i = 0;
	if (!s1)
		s1 = ft_strdup_chr("", len, check);
	while (s2[i] && s2[i] != '\n')
		i++;
	if (s2[i] == '\n')
	{
		i++;
		*check = i;
	}
	else
		*check = 0;
	join = malloc(sizeof(*join) * (*len + i + 1));
	if (!join)
		return (NULL);
	ft_memcpy_ret(join, s1, *len);
	ft_memcpy_ret(&join[*len], s2, i);
	*len += i;
	join[*len] = '\0';
	free(s1);
	return (join);
}
