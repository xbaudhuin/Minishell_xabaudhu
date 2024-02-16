/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:07:33 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/16 12:16:36 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_str_array(char **string_array)
{
	size_t	str_num;

	str_num = 0;
	while (string_array[str_num] != NULL)
	{
		free(string_array[str_num]);
		++str_num;
	}
	free(string_array);
}
