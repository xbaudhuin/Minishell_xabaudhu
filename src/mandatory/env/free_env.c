/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:26:14 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/17 13:26:14 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	free_env(t_env env)
{
	size_t	var_num;

	var_num = 0;
	while (var_num < env.allocated_size)
	{
		free(env.variables[var_num]);
		++var_num;
	}
	free(env.variables);
}
