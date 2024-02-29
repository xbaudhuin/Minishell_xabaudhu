/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_builtin_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:40:40 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/28 18:40:41 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dup_std(int save_std[2])
{
	save_std[0] = dup(STDIN_FILENO);
	if (save_std[0] == INVALID_FD)
	{
		ft_fprintf(2, "minishell: launch_builtin: %s\n", strerror(errno));
		return (FAILURE);
	}
	save_std[1] = dup(STDOUT_FILENO);
	if (save_std[1] == INVALID_FD)
	{
		close(save_std[0]);
		ft_fprintf(2, "minishell: launch_builtin: %s\n", strerror(errno));
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	close_on_dup2_fail(int save_std[2], int infile, int outfile)
{
	ft_fprintf(2, "minishell: launch_builtin: %s\n", strerror(errno));
	close(save_std[0]);
	close(save_std[1]);
	if (infile != STDIN_FILENO || isatty(infile) == FALSE)
	{
		close(infile);
	}
	if (outfile != STDOUT_FILENO || isatty(outfile) == FALSE)
	{
		close(outfile);
	}
	return (FAILURE);
}

int	set_builtin_redirection(t_exec_cmd *cmd, t_token *redirect_token, int save_std[2])
{
	if (dup_std(save_std) == FAILURE)
		return (FAILURE);
	if (open_cmd_files(redirect_token, cmd) == FAILURE)
	{
		close(save_std[0]);
		close(save_std[1]);
		return (FAILURE);
	}
	if (cmd->infile != STDIN_FILENO)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == INVALID_FD)
			return (close_on_dup2_fail(save_std, cmd->infile, cmd->outfile));
		close(cmd->infile);
	}
	if (cmd->outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == INVALID_FD)
			return (close_on_dup2_fail(save_std, cmd->infile, cmd->outfile));		
		close(cmd->outfile);
	}
	return (SUCCESS);
}