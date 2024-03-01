/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_cmd_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:49:55 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/03/01 14:49:56 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_cmd_files(t_exec_cmd *cmd)
{
	if (cmd->infile != STDIN_FILENO)
	{
		close(cmd->infile);
	}
	if (cmd->outfile != STDOUT_FILENO)
	{
		close(cmd->outfile);
	}
	if (isatty(STDIN_FILENO) == FALSE)
	{
		close(STDIN_FILENO);
	}
	if (isatty(STDOUT_FILENO) == FALSE)
	{
		close(STDOUT_FILENO);
	}
	return (SUCCESS);
}