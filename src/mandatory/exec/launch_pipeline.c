/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:08:41 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/28 16:08:42 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipe_fd(t_data *data)
{
	if (data->tmp_fd != INVALID_FD)
	{
		close(data->tmp_fd);
	}
	if (data->pipe_fd[READ_SIDE] != INVALID_FD)
	{
		close(data->pipe_fd[READ_SIDE]);
	}
	if (data->pipe_fd[WRITE_SIDE] != INVALID_FD)
	{
		close(data->pipe_fd[READ_SIDE]);
	}
}

static int	fail_open_pipe(t_data *data)
{
	close(data->pipe_fd[READ_SIDE]);
	get_last_child_status(0);
	return (FAILURE);
}

static void	do_child(t_exec_cmd **exec_cmd, int cmd_num, t_data data,
	t_command **cmd)
{
	int	builtin_return;

	handle_sigint(DEFAULT);
	handle_sigquit(FALSE);
	if (set_pipe_redirection(&data, cmd_num) == FAILURE)
	{
		end_process(exec_cmd[cmd_num], data, FAILURE);
	}
	if (is_builtin((const char **) exec_cmd[cmd_num]->argv) != NONE)
	{
		builtin_return = launch_builtin(exec_cmd[cmd_num],
				cmd[cmd_num]->redirect_token, &data);
		end_process(exec_cmd[cmd_num], data, builtin_return);
	}
	else
	{
		execute_a_cmd(exec_cmd[cmd_num], cmd[cmd_num]->redirect_token, data);
	}
}

int	launch_pipeline(t_command **cmd, t_exec_cmd **exec_cmd, t_data data)
{
	int		cmd_num;
	pid_t	pid;
	pid_t	pgid;

	cmd_num = 0;
	pgid = 0;
	while (exec_cmd[cmd_num] != NULL)
	{
		if (open_pipe(&data, cmd_num) == FAILURE)
		{
			return (fail_open_pipe(&data));
		}
		pid = fork();
		if (pid == -1)
		{
			close_pipe_fd(&data);
			get_last_child_status(0);
			return (FAILURE);
		}
		else if (pid == 0)
		{
			do_child(exec_cmd, cmd_num, data, cmd);
		}
		if (pgid == 0)
			pgid = pid;
		++cmd_num;
	}
	close(data.pipe_fd[READ_SIDE]);
	return (get_last_child_status(pid));
}
