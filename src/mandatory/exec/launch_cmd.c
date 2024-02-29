/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:30:42 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/22 18:30:43 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	close_files(t_exec_cmd *cmd)
{
	if (cmd->infile != STDIN_FILENO || isatty(cmd->infile) == FALSE)
	{
		close(cmd->infile);
	}
	if (cmd->outfile != STDOUT_FILENO || isatty(cmd->outfile) == FALSE)
	{
		close(cmd->outfile);
	}
	if (isatty(STDIN_FILENO) == FALSE)
		close(STDIN_FILENO);
	if (isatty(STDOUT_FILENO) == FALSE)
		close(STDOUT_FILENO);
	return (SUCCESS);
}

static int	set_cmd_redirection(t_exec_cmd *cmd)
{
	if (cmd->infile != STDIN_FILENO)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == INVALID_FD)
		{
			ft_fprintf(2, "minishell: launch_cmd: %s\n", strerror(errno));
			close_files(cmd);
			return (FAILURE);
		}
	}
	if (cmd->outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == INVALID_FD)
		{
			ft_fprintf(2, "minishell: launch_cmd: %s\n", strerror(errno));
			close_files(cmd);
			return (FAILURE);
		}		
	}
	return (SUCCESS);
}

static void	end_child(t_exec_cmd *exec_cmd, t_data data, int exit_status)
{
	close_files(exec_cmd);
	end_process(data, exit_status);
}

static void	launch_child(t_exec_cmd *exec_cmd,
	t_token *redirect_token, t_data data)
{
	int	exit_status;

	exit_status = SUCCESS;
	if (open_cmd_files(redirect_token, exec_cmd) == FAILURE)
		end_process(data, FAILURE);
	if (set_cmd_redirection(exec_cmd) == FAILURE)
		end_process(data, FAILURE);
	if (exec_cmd->argv[0] == NULL)
		end_child(exec_cmd, data, SUCCESS);
	exec_cmd->path = get_cmd_path((const char *)exec_cmd->argv[0],
			(const t_env) * data.env, &exit_status);
	if (exec_cmd->path == NULL)
		end_child(exec_cmd, data, exit_status);
	if (access(exec_cmd->path, X_OK) == -1)
	{
		ft_fprintf(2, "minishell: %s :%s\n", exec_cmd->path, strerror(errno));
		end_process(data, 126);
	}
	execve(exec_cmd->path, exec_cmd->argv, data.env->variables);
	close_files(exec_cmd);
	end_process(data, FAILURE);
}

int	launch_cmd(t_exec_cmd *exec_cmd, t_token *redirect_token, t_data data)
{
	int	pid;
	int	exit_status;

	exit_status = SUCCESS;
	pid = fork();
	if (pid == -1)
	{
		return (FAILURE);
	}
	else if (pid == 0)
	{
		launch_child(exec_cmd, redirect_token, data);
	}
	else
	{
		waitpid(pid, &exit_status, 0);
		if (WIFEXITED(exit_status))
				exit_status = WEXITSTATUS(exit_status);
	}
	return (exit_status);
}
