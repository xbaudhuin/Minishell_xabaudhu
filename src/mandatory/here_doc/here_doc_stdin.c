/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_stdin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:28:04 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/04 13:08:04 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	global;

void	get_stdin(t_token *here_doc, char *limiter, unsigned int len_lim)
{
	char			*line;
	int				save_std;

	save_std = dup(STDIN_FILENO);
	if (save_std == INVALID_FD)
		return ;
	handle_sigint(CLOSE_IN);
	here_doc->len_word = 0;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_fprintf(2, "minishell: warning: here_document "
				"delimited by end-of-file wanted: %s\n", limiter);
			break ;
		}
		if (ft_strncmp(limiter, line, len_lim + 1) == 0)
			break ;
		here_doc->word = ft_strjoin_free_s1(
				here_doc->word, line, &here_doc->len_word);
		if (here_doc->word == NULL)
		{
			here_doc->type = ERROR;
			return ;
		}
		free(line);
	}
	if (dup2(save_std, STDIN_FILENO) == INVALID_FD)
	{
		handle_sigint(NEW_PROMPT);
		close(save_std);
		return ;
	}
	handle_sigint(NEW_PROMPT);
	close(save_std);
	free(line);
}
