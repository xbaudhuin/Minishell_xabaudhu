/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_var_name_valid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:03:21 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/20 17:03:25 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_name_valid(const char *arg)
{
	size_t	char_num;

	if (is_underscore(arg[0]) == FALSE && ft_isalpha(arg[0]) == FALSE)
	{
		return (FALSE);
	}
	char_num = 1;
	while (arg[char_num] != '\0' && arg[char_num] != '=')
	{
		if (is_underscore(arg[char_num]) == FALSE
			&& ft_isalnum(arg[char_num]) == FALSE)
		{
			return (FALSE);
		}
		++char_num;
	}
	return (TRUE);
}
