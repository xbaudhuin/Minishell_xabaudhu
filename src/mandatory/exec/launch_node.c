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

static int	get_nb_cmd(const t_exec_cmd **exec_cmd)
{
	int	nb_cmd;

	nb_cmd = 0;
	while (exec_cmd[nb_cmd] != NULL)
	{
		++nb_cmd;
	}
	return (nb_cmd);
}

static int	get_launch_type(const t_exec_cmd **exec_cmd)
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

static t_data	set_data(t_env *env, t_node *root, t_exec_cmd **exec_cmd)
{
	t_data	data;

	data.env = env;
	data.exec_cmd = exec_cmd;
	data.root = root;
	return (data);
}

int	launch_node(t_command **cmd, t_env *env, t_node *root)
{
	t_exec_cmd	**exec_cmd;
	t_data		data;
	int			launch_type;

	
	exec_cmd = initialize_exec_cmd((const t_command **)cmd);
	if (exec_cmd == NULL)
		return (FAILURE);
	data = set_data(env, root, exec_cmd);
	launch_type = get_launch_type((const t_exec_cmd **)exec_cmd);
	if (launch_type == LAUNCH_BUILTIN)
	{
		env->exit_status = launch_builtin(exec_cmd[0], cmd[0]->redirect_token, env);
		free_exec_cmd(exec_cmd);
		return (env->exit_status);
	}
	else if (launch_type == LAUNCH_CMD)
	{
		env->exit_status = launch_cmd(exec_cmd[0], cmd[0]->redirect_token, data);
		free_exec_cmd(exec_cmd);
		return (env->exit_status);
	}
	return (SUCCESS);
}