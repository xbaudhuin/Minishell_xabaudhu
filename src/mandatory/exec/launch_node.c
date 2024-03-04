/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:09:02 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/03/04 14:57:56 by xabaudhu         ###   ########.fr       */
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

static int	get_launch_type(const t_data data)
{
	if (data.nb_cmd > 1)
	{
		return (LAUNCH_PIPELINE);
	}
	else if (is_builtin((const char **)data.exec_cmd[0]->argv) != NONE)
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
	data.tmp_fd = INVALID_FD;
	data.pipe_fd[READ_SIDE] = INVALID_FD;
	data.pipe_fd[WRITE_SIDE] = INVALID_FD;
	data.save_std[STDIN_FILENO] = INVALID_FD;
	data.save_std[STDOUT_FILENO] = INVALID_FD;
	data.nb_cmd = get_nb_cmd((const t_exec_cmd **)exec_cmd);
	return (data);
}

int	launch_node(t_command **cmd, t_env *env, t_node *root)
{
	t_exec_cmd	**exec_cmd;
	t_data		data;
	int			launch_type;

	if (expand_token(cmd, (const t_env) * env) == FAILURE)
		return (FAILURE);
	exec_cmd = initialize_exec_cmd((const t_command **)cmd);
	if (exec_cmd == NULL)
		return (FAILURE);
	data = set_data(env, root, exec_cmd);
	launch_type = get_launch_type(data);
	if (launch_type == LAUNCH_BUILTIN)
	{
		env->exit_status = launch_builtin(exec_cmd[0],
				cmd[0]->redirect_token, &data);
	}
	else if (launch_type == LAUNCH_CMD)
	{
		env->exit_status = launch_cmd(exec_cmd[0],
				cmd[0]->redirect_token, data);
	}
	else
	{
		env->exit_status = launch_pipeline(cmd, exec_cmd, data);
	}
	free_exec_cmd(exec_cmd);
	return (env->exit_status);
}
