/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_var_address.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:44:03 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/03/04 19:44:03 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_last_var_address(const t_env env)
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
