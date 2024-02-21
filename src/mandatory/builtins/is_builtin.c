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

int	is_this_builtin(int index, char *cmd_name)
{
	char	*builtins[NB_BUILTIN];

	if (index >= NB_BUILTIN)
		return (FAILURE);
	builtins[ECHO] = "echo";
	builtins[CD] = "cd";
	builtins[PWD] = "pwd";
	builtins[EXPORT] = "export";
	builtins[UNSET] = "unset";
	builtins[ENV] = "env";
	builtins[EXIT] = "exit";
	if (ft_strncmp(cmd_name, builtins[index],
			ft_strlen(builtins[index]) + 1) == SUCCESS)
	{
		return (TRUE);
	}
	return (FALSE);
}

int	is_builtin(const char **argv)
{
	char	*cmd_name;
	int		builtin_num;

	builtin_num = 0;
	cmd_name = (char *)argv[0];
	while (builtin_num < NB_BUILTIN)
	{
		if (is_this_builtin(builtin_num, cmd_name) == TRUE)
		{
			return (builtin_num);
		}
		++builtin_num;
	}
	return (builtin_num);
}
