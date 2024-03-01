/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_a_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:04:50 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/03/01 18:08:13 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_a_cmd(t_exec_cmd *exec_cmd,
	t_token *redirect_token, t_data data)
{
	int	exit_status;

	exit_status = SUCCESS;
	if (open_cmd_files(redirect_token, exec_cmd) == FAILURE)
	{
		end_process(exec_cmd, data, FAILURE);
	}
	if (set_cmd_redirection(exec_cmd) == FAILURE)
	{
		end_process(exec_cmd, data, FAILURE);
	}
	if (exec_cmd->argv[0] == NULL)
	{
		end_process(exec_cmd, data, SUCCESS);
	}
	exec_cmd->path = get_cmd_path((const char *)exec_cmd->argv[0],
			(const t_env) * data.env, &exit_status);
	if (exec_cmd->path == NULL)
	{
		end_process(exec_cmd, data, exit_status);
	}
	if (access(exec_cmd->path, X_OK) == -1)
	{
		ft_fprintf(2, "minishell: %s :%s\n", exec_cmd->path, strerror(errno));
		end_process(exec_cmd, data, 126);
	}
	execve(exec_cmd->path, exec_cmd->argv, data.env->variables);
	end_process(exec_cmd, data, FAILURE);
}
