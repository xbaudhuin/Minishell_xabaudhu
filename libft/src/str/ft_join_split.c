/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:32:14 by xabaudhu          #+#    #+#             */
/*   Updated: 2023/12/06 16:24:06 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <string.h>
//#include <bsd/string.h>
#include <stdio.h>

static	size_t	*get_len(size_t *len_join, int *n, char **split)
{
	int		i;
	size_t	*len;
	int		size_split;

	i = 0;
	*len_join = 0;
	size_split = 0;
	while (split[size_split])
		size_split++;
	if (size_split < *n)
		*n = size_split;
	len = malloc(*n * sizeof(size_t));
	if (!len)
		return (NULL);
	while (i < *n)
	{
		len[i] = ft_strlen(split[i]);
		*len_join += len[i];
		i++;
	}
	return (len);
}

char	*ft_join_split(char **split, int n, char c)
{
	int		i;
	size_t	*len;
	size_t	len_join;
	char	*join;

	if (n <= 0 || !split || !*split)
		return (NULL);
	len = get_len(&len_join, &n, split);
	if (!len)
		return (NULL);
	join = malloc(sizeof(*join) * (len_join + n));
	if (!join)
		return (NULL);
	i = -1;
	len_join = 0;
	while (++i < n)
	{
		ft_memmove(&join[len_join], split[i], len[i]);
		len_join += len[i];
		if (i != n - 1)
			join[len_join++] = c;
	}
	join[len_join] = '\0';
	return (free(len), join);
}
