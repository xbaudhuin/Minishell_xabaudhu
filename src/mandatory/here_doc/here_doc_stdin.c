/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_stdin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:28:04 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/06 12:28:11 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	global;

int	get_stdin(t_token *here_doc, char *limiter, unsigned int len_lim)
{
	char			*line;

	here_doc->len_word = 0;
	while (1)
	{
		line = readline("here_doc> ");
		if (line == NULL)
		{
			if (global == 0)
				ft_fprintf(2, "minishell: warning: here_document"
					"delimited by end-of-file wanted: %s", limiter);
			break ;
		}
		if (ft_strncmp(limiter, line, len_lim + 1) == 0)
			break ;
		here_doc->word = ft_strjoin_free_s1(
				here_doc->word, line, &here_doc->len_word);
		if (here_doc->word == NULL)
		{
			here_doc->type = ERROR;
			break ;
		}
		free(line);
	}
	free(line);
	if (global == 130)
		return (SIGINT);
	return (SUCCESS);
}
