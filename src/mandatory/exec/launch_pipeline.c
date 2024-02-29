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

static int	open_pipe(t_data *data, int cmd_num)
{
	if (cmd_num > 0)
	{
		if (cmd_num > 1)
			close(data->tmp_fd);
		close(data->pipe_fd[1]);
		data->tmp_fd = data->pipe_fd[0];
	}
	if (cmd_num < data->nb_cmd - 1)
	{
		if (pipe(data->pipe_fd) == -1)
		{
			ft_fprintf(2, "minishell: launch_pipeline: %s\n", strerror(errno));
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

static int	set_pipe_redirection(t_data *data, int cmd_num)
{
	int	error;

	error = SUCCESS;
	if (cmd_num == 0)
	{
		close(data->pipe_fd[0]);
		if (dup2(data->pipe_fd[1], STDOUT_FILENO) == FAILURE);
			error = FAILURE;
		close(data->pipe_fd[1]);
	}
	else if (cmd_num == data->nb_cmd - 1)
	{
		if (dup2(data->tmp_fd, STDIN_FILENO) == FAILURE)
			error = FAILURE;
		close(data->tmp_fd);
	}
	else
	{
		close(data->pipe_fd[0]);
		if (dup2(data->pipe_fd[1], STDOUT_FILENO) == FAILURE
			|| dup2(data->tmp_fd, STDIN_FILENO) == FAILURE)
			error = FAILURE;
		close(data->pipe_fd[1]);
		close(data->tmp_fd);
	}
	return (error);
}

static void	launch_child(t_exec_cmd *exec_cmd, t_token *redirection, t_data data, int cmd_num)
{
	int	exit_status;

	exit_status = SUCCESS;
	if (open_cmd_files(redirection, exec_cmd) == FAILURE)
		end_process(data, FAILURE);
	if (set_cmd_redirection(exec_cmd) == FAILURE)
		end_process(data, FAILURE);
	if (exec_cmd->argv[0] == NULL)
		end_process(data, SUCCESS);
	exec_cmd->path = get_cmd_path((const char *)exec_cmd->argv[0],
			(const t_env) * data.env, &exit_status);
	if (exec_cmd->path == NULL)
		end_process(data, exit_status);
	if (access(exec_cmd->path, X_OK) == -1)
	{
		ft_fprintf(2, "minishell: %s :%s\n", exec_cmd->path, strerror(errno));
		end_process(data, 126);
	}
	execve(exec_cmd->path, exec_cmd->argv, data.env->variables);
	exit(FAILURE);
}

//Envoyer pour chaque fork (donc chaque commande du pipeline) son
//*redirect_token et son *exec_cmd en plus des pipe_fd
int	launch_pipeline(t_command **cmd, t_exec_cmd **exec_cmd , t_data data)
{
	int	cmd_num;
	int	pid;

	cmd_num = 0;
	while (exec_cmd[cmd_num] != NULL)
	{
		open_pipe(&data, cmd_num);
		pid = fork();
		if (pid == -1)
			return (FAILURE);
		else if (pid == 0)
		{
			if (set_pipe_redirection(&data, cmd_num) == FAILURE)
			{
				end_process(data, FAILURE);
			}
			launch_child(exec_cmd[cmd_num], cmd[cmd_num]->redirect_token, data, cmd_num);
		}
		++cmd_num;
	}
	//close(data.pipe_fd[0]);
	return (get_last_child_status(pid));
}
