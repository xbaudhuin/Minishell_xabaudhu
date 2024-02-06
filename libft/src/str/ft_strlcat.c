/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:28:23 by xabaudhu          #+#    #+#             */
/*   Updated: 2023/10/19 16:16:41 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	n;

	n = size;
	i = 0;
	j = 0;
	while (n != 0 && dst[i])
	{
		i++;
		n--;
	}
	n = size - i;
	if (n == 0)
		return (i + ft_strlen(src));
	while (src[j] && n > 1)
	{
		dst[i + j] = src[j];
		j++;
		n--;
	}
	dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
