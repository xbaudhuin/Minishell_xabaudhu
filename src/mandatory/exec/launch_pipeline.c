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
				end_process(exec_cmd[cmd_num], data, FAILURE);
			}
			execute_a_cmd(exec_cmd[cmd_num], cmd[cmd_num]->redirect_token, data);
		}
		++cmd_num;
	}
	close(data.pipe_fd[0]);
	return (get_last_child_status(pid));
}
