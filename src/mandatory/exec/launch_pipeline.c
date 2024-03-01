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

static void	launch_child(t_exec_cmd *exec_cmd, t_token *redirection, t_data data)
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
	{
		close_cmd_files(exec_cmd);
		end_process(data, exit_status);
	}
	if (access(exec_cmd->path, X_OK) == -1)
	{
		ft_fprintf(2, "minishell: %s :%s\n", exec_cmd->path, strerror(errno));
		close_cmd_files(exec_cmd);
		end_process(data, 126);
	}
	execve(exec_cmd->path, exec_cmd->argv, data.env->variables);
	close_cmd_files(exec_cmd);
	end_process(data, FAILURE);
}

//Envoyer pour chaque fork (donc chaque commande du pipeline) son
//*redirect_token et son *exec_cmd en plus des pipe_fd
int	launch_pipeline(t_command **cmd, t_exec_cmd **exec_cmd , t_data data)
{
	int		cmd_num;
	pid_t	pid;

	cmd_num = 0;
	while (exec_cmd[cmd_num] != NULL)
	{
		open_pipe(&data, cmd_num);
		pid = fork();
		if (pid == -1)
			return (FAILURE);
		else if (pid == 0)
		{
			handle_sigquit(FALSE);
			handle_sigint(FALSE);
			if (set_pipe_redirection(&data, cmd_num) == FAILURE)
			{
				close_cmd_files(exec_cmd[cmd_num]);
				end_process(data, FAILURE);
			}
			launch_child(exec_cmd[cmd_num], cmd[cmd_num]->redirect_token, data);
		}
		++cmd_num;
	}
	close(data.pipe_fd[0]);
	return (get_last_child_status(pid));
}
