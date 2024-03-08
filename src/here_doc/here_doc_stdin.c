/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_stdin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:28:04 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/07 18:21:30 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_global;

static int	initialize_read(int *save_std, t_token *here_doc)
{
	*save_std = dup(STDIN_FILENO);
	if (*save_std == INVALID_FD)
	{
		here_doc->type = FAIL_DUP;
		return (FAILURE);
	}
	handle_sigint(CLOSE_IN);
	return (SUCCESS);
}

static int	restore_read(int save_std, t_token *here_doc)
{
	if (dup2(save_std, STDIN_FILENO) == INVALID_FD)
	{
		handle_sigint(NEW_PROMPT);
		close(save_std);
		perror(RED"Fail to save_back STDIN"RESET);
		here_doc->type = FAIL_DUP;
		return (FAILURE);
	}
	handle_sigint(NEW_PROMPT);
	close(save_std);
	if (g_global == 1)
	{
		here_doc->type = FAIL_MALLOC;
		return (FAILURE);
	}
	else
		return (SUCCESS);
}

static char	*get_token_word(t_token *here_doc,
	char *limiter, unsigned int len_lim)
{
	char	*word;
	char	*line;

	word = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			if (g_global == 0)
				ft_fprintf(2, "minishell: warning: here_document"
					"delimited by end-of-file wanted: %s\n", limiter);
			break ;
		}
		if (ft_strncmp(limiter, line, len_lim + 1) == 0)
			break ;
		word = ft_strjoin_free_s1(word, line, &here_doc->len_word);
		if (word == NULL)
		{
			here_doc->type = FAIL_MALLOC;
			break ;
		}
		free(line);
	}
	return (free(line), word);
}

int	get_stdin(t_token *here_doc, char *limiter, unsigned int len_lim)
{
	int				save_std;

	if (initialize_read(&save_std, here_doc) != SUCCESS)
		return (FAILURE);
	here_doc->len_word = 0;
	here_doc->word = get_token_word(here_doc, limiter, len_lim);
	if (restore_read(save_std, here_doc) == SUCCESS)
		return (SUCCESS);
	else
		return (FAILURE);
}
