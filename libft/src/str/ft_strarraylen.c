/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarraylen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:03:42 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/16 12:03:43 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strarraylen(const char **string_array)
{
	size_t	array_len;

	array_len = 0;
	while (string_array[array_len] != NULL)
	{
		++array_len;
	}
	return (array_len);
}
