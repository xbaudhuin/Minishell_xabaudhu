/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:24:12 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/03/04 11:24:14 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_shlvl(t_env env)
{
	char	*argv[3];

	argv[0] = "export";
	argv[1] = "SHLVL=1";
	argv[2] = NULL;
	export((const char **)argv, &env);
}
