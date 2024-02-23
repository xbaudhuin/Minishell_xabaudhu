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

int	open_cmd_infile(t_token *redir_token)
{
	int		infile_fd;
	char	*path;

	path = redir_token->word;
	infile_fd = open(path, O_RDONLY);
	if (infile_fd == INVALID_FD)
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

int	open_cmd_infile(t_token *redir_token)
{
	int		outfile_fd;
	char	*path;

	path = redir_token->word;
	if (redir_token->type == REDIRECT_OUT)
	{
		outfile_fd = open(path, O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		outfile_fd = open(path, O_CREAT | O_APPEND, 0644);
	}
	if (outfile_fd == INVALID_FD)
	{
		ft_fprintf(2, "minishel: %s :%s\n", path, strerror(errno));
	}
	if (isatty(outfile_fd) == SUCCESS)
	{
		close(outfile_fd);
		return (TTY);
	}
	else
	{
		return (outfile_fd);
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
			tmp_fd = open_cmd_infile(tmp_redir_token);
			if (tmp_fd != TTY)
			{
				if (cmd->infile != INVALID_FD)
					close(cmd->infile);
				cmd->infile = tmp_fd;
			}
		}
		tmp_redir_token = tmp_redir_token->next;
	}
}