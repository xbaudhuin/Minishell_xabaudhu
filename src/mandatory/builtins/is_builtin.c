/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:17:03 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/20 19:17:04 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**set(void)
{
	char	*builtins[NB_BUILTIN];

	builtins[ECHO] = "echo";
	builtins[CD] = "cd";
	builtins[PWD] = "pwd";
	builtins[EXPORT] = "export";
	builtins[UNSET] = "unset";
	builtins[ENV] = "env";
	builtins[EXIT] = "exit";
	return (builtins);
}

int	is_builtin(const char **argv)
{
	char	**builtins;
	char	*cmd_name;
	int		builtin_num;

	builtin_num = 0;
	cmd_name = argv[0];
	builtins = set();
	while (builtin_num < NB_BUILTIN)
	{
		if (ft_strncmp(cmd_name, builtins[builtin_num], ft_strlen(builtins[builtin_num]) + 1) == SUCCESS)
		{
			return (builtin_num);
		}
		++builtin_num;
	}
	return (builtin_num);
}
