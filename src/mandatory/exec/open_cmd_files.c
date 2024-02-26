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

static int	open_cmd_infile(t_token *redir_token)
{
	int		infile_fd;
	char	*path;

	path = redir_token->word;
	infile_fd = open(path, O_RDONLY);
	if (infile_fd == INVALID_FD)
	{
		ft_fprintf(2, "minishell: %s :%s\n", path, strerror(errno));
		return (infile_fd);
	}
	if (isatty(infile_fd) == TRUE)
	{
		close(infile_fd);
		return (TTY);
	}
	else
	{
		return (infile_fd);
	}
}

static int	open_cmd_here_doc(t_token *redir_toen)
{
	int		pipe_fd[2];
	char	*here_doc_content;

	here_doc_content = redir_toen->word;
	if (pipe(pipe_fd) == -1)
	{
		ft_fprintf(2, "minishell: here doc :%s\n", strerror(errno));
		return (INVALID_FD);
	}
	write(pipe_fd[0], here_doc_content, ft_strlen(here_doc_content));
	close(pipe_fd[0]);
	return (pipe_fd[1]);
}

static int	open_cmd_outfile(t_token *redir_token, int redir_type)
{
	int		outfile_fd;
	char	*path;

	path = redir_token->word;
	if (redir_type == REDIRECT_OUT)
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
		return (outfile_fd);
	}
	if (isatty(outfile_fd) == TRUE)
	{
		return (close(outfile_fd), TTY);
	}
	else
	{
		return (outfile_fd);
	}
}

static int	get_fd(t_token *redir_token, int old_fd, int redir_type)
{
	int	new_fd;

	if (redir_type == REDIRECT_IN)
	{
		new_fd = open_cmd_infile(redir_token);
	}
	else if (redir_type == REDIRECT_OUT || redir_type == APPEND_OUT)
	{
		new_fd = open_cmd_outfile(redir_token, redir_type);
	}
	else
	{
		new_fd = open_cmd_here_doc(redir_token);
	}
	if (new_fd != TTY)
	{
		if (old_fd != INVALID_FD && old_fd != STDIN_FILENO
			&& old_fd != STDOUT_FILENO)
			close(old_fd);
		return (new_fd);
	}
	else
	{
		return (old_fd);
	}
}

int	open_cmd_files(t_command *cmd)
{
	t_token	*tmp_redir_token;
	int		redir_type;

	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	tmp_redir_token = cmd->redirect_token;
	while (tmp_redir_token != NULL)
	{
		redir_type = tmp_redir_token->type;
		if (redir_type == REDIRECT_IN)
		{
			cmd->infile = get_fd(tmp_redir_token, cmd->infile, redir_type);
		}
		else if (redir_type == REDIRECT_OUT || redir_type == APPEND_OUT)
		{
			cmd->outfile = get_fd(tmp_redir_token, cmd->outfile, redir_type);
		}
		else if (tmp_redir_token->type == HERE_DOC)
		{
			cmd->infile = get_fd(tmp_redir_token, cmd->infile, redir_type);
		}
		if (cmd->infile == INVALID_FD || cmd->outfile == INVALID_FD)
			return (FAILURE);
		tmp_redir_token = tmp_redir_token->next;
	}
	return (SUCCESS);
}
