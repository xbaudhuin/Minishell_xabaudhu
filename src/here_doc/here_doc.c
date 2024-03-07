/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:30:55 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/07 18:51:52 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_handle_list(t_token *here_doc, t_token **head)
{
	t_token	*redirect;

	redirect = here_doc->previous;
	here_doc->type = redirect->type;
	if (redirect->previous == NULL)
	{
		(*head) = here_doc;
		ft_del_token(redirect);
		here_doc->previous = NULL;
	}
	else
	{
		redirect->previous->next = here_doc;
		here_doc->previous = redirect->previous;
		ft_del_token(redirect);
	}
}

int	do_here_doc(t_token *here_doc, t_token **head, int *previous_type)
{
	char	*limiter;

	if (head == NULL || *head == NULL || here_doc->word == NULL)
		return (FAILURE);
	*previous_type = ERROR;
	here_doc_handle_list(here_doc, head);
	if (ft_strchr(here_doc->word, '\'') == NULL
		&& ft_strchr(here_doc->word, '"') == NULL)
		here_doc->type = HERE_DOC;
	else
		here_doc->type = HERE_DOC_NO_EXPAND;
	limiter = get_limiter(here_doc);
	if (limiter == NULL)
		return (FAILURE);
	if (get_stdin(here_doc, limiter, here_doc->len_word) != SUCCESS)
	{
		here_doc->type = ERROR;
	}
	free(limiter);
	if (here_doc->word == NULL)
	{
		here_doc->word = ft_strdup("");
		if (here_doc->word == NULL)
		{
			perror(RED"do_here_doc"RESET);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
