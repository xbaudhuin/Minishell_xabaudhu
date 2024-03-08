/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:34:15 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/08 14:43:08 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include <dirent.h>
#include <errno.h>

int	is_wildcard_expandable(const char *word, const int type)
{
	unsigned int	i;
	char			quotes;

	i = 0;
	quotes = '\0';
	if (is_here_doc_token(type) == TRUE)
		return (FALSE);
	while (word[i] != '\0')
	{
		if (is_quotes(word[i]))
		{
			quotes = word[i];
			i++;
			while (word[i] && word[i] != quotes)
				i++;
			i++;
		}
		else if (word[i] == '*')
			return (TRUE);
		else
			i++;
	}
	return (FALSE);
}

int	expand_wildcard_list(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (is_wildcard_expandable(tmp->word, tmp->type) == TRUE)
		{
			printf(RED"TRUE\n"RESET);
			tmp->word = do_expand_wildcard(tmp->word);
			if (tmp->word == NULL)
			{
				free_token(head);
				return (FAILURE);
			}
			if (re_tokenize(tmp) == FAILURE)
			{
				free_token(head);
				return (FAILURE);
			}
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	expand_wildcard(t_command **cmd)
{
	unsigned int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->token)
		{
			if (expand_wildcard_list(&cmd[i]->token) == FAILURE)
				return (FAILURE);
		}
		if (cmd[i]->redirect_token)
		{
			if (expand_wildcard_list(&cmd[i]->redirect_token) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
