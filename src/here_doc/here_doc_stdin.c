/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_stdin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:28:04 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/08 15:17:19 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

extern int	g_global;

int	get_stdin(t_token *here_doc, char *limiter, unsigned int len_lim)
{
	char			*line;
	int				save_std;

	save_std = dup(STDIN_FILENO);
	if (save_std == INVALID_FD)
	{
		here_doc->type = FAIL_DUP;
		return (FAILURE);
	}
	handle_sigint(CLOSE_IN);
	here_doc->len_word = 0;
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
		here_doc->word = ft_strjoin_free_s1(
				here_doc->word, line, &here_doc->len_word);
		if (here_doc->word == NULL)
		{
			here_doc->type = FAIL_MALLOC;
			break ;
		}
		free(line);
	}
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
	free(line);
	return (SUCCESS);
}
