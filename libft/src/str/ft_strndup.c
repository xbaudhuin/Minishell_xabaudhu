/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:49:30 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/16 13:01:17 by xabaudhu         ###   ########.fr       */
/*   Updated: 2024/02/14 16:11:21 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	adjust_n(const char *str, size_t n)
{
	size_t	len_str;

	len_str = ft_strlen(str);
	if (len_str < n)
		n = len_str;
	return (n);
}

char	*ft_strndup(const char *str, size_t n)
{
	char	*dup;

	n = adjust_n(str, n);
	dup = malloc(sizeof(*dup) * (n + 1));
	if (!dup)
		return (NULL);
	ft_memmove(dup, str, n);
	dup[n] = '\0';
	return (dup);
}
