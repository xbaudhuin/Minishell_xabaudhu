/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:15:16 by xabaudhu          #+#    #+#             */
/*   Updated: 2023/10/19 17:10:46 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*cal;
	size_t	total;

	total = nmemb * size;
	if (!total)
		total = 1;
	else if (total / size != nmemb)
		return (NULL);
	cal = malloc(total);
	if (!cal)
		return (NULL);
	ft_bzero(cal, total);
	return (cal);
}
