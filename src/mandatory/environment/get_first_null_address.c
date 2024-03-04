/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_first_null_address.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:24:39 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/03/04 11:24:40 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_first_null_address(const t_env env)
{
	int	var_num;

	var_num = env.allocated_size - 1;
	while (var_num > 0)
	{
		if (env.variables[var_num] != NULL)
		{
			break ;
		}
		--var_num;
	}
	return (&env.variables[var_num]);
}
