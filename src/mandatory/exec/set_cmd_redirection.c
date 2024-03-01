/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:52:27 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/03/01 14:52:28 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_cmd_redirection(t_exec_cmd *cmd)
{
	if (cmd->infile != STDIN_FILENO)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == INVALID_FD)
		{
			ft_fprintf(2, "minishell: launch_cmd: %s\n", strerror(errno));
			return (FAILURE);
		}
		close (cmd->infile);
	}
	if (cmd->outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == INVALID_FD)
		{
			ft_fprintf(2, "minishell: launch_cmd: %s\n", strerror(errno));
			return (FAILURE);
		}
		close(cmd->outfile);
	}
	return (SUCCESS);
}
