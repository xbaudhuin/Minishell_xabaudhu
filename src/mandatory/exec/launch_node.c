/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:09:02 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/27 19:09:03 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nb_cmd(t_exec_cmd **exec_cmd)
{
	int	nb_cmd;

	nb_cmd = 0;
	while (exec_cmd[nb_cmd] != NULL)
	{
		++nb_cmd;
	}
	return (nb_cmd);
}

static int	get_launch_type(t_exec_cmd **exec_cmd)
{
	int	nb_cmd;

	nb_cmd = get_nb_cmd(exec_cmd);
	if (nb_cmd > 1)
	{
		return (LAUNCH_PIPELINE);
	}
	else if (is_builtin((const char **)exec_cmd[0]->argv) != NONE)
	{
		return (LAUNCH_BUILTIN);
	}
	else
	{
		return (LAUNCH_CMD);
	}
}

int	launch_node(t_command **cmd, t_env *env)
{
	t_exec_cmd	**exec_cmd;

	(void)env;
	exec_cmd = initialize_exec_cmd(cmd);
	if (exec_cmd == NULL)
		return (FAILURE);
	exit(get_launch_type(exec_cmd));
	return (1);
}