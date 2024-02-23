/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_cmd_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:44:55 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/23 17:44:58 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	open_cmd_infile(t_token *redir_token)
{
	int		infile_fd;
	char	*path;

	path = redir_token->word;
	if (infile_fd == - 1)
	{
		ft_fprintf(2, "minishel: %s :%s\n", path, strerror(errno));
	}
	if (isatty(infile_fd) == SUCCESS)
	{
		close(infile_fd);
		return (TTY);
	}
	else
	{
		return (infile_fd);
	}
}

int	open_cmd_files(t_command *cmd)
{
	t_token	*tmp_redir_token;
	int		tmp_fd;

	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	tmp_redir_token = cmd->redirect_token;
	while (tmp_redir_token != NULL)
	{
		if (tmp_redir_token->type = REDIRECT_IN)
		{
			tmp_fd = open_cmd_infile(tmp_redir_token)
		}
	}
}