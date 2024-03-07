/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:34:15 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/06 18:22:43 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <errno.h>

int	is_wildcard_expandable(const char *word)
{
	if (get_nb_wildcard(word, '*') >= 1)
		return (TRUE);
	return (FALSE);
}

int	expand_wildcard_list(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (is_wildcard_expandable(tmp->word) == TRUE)
		{
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
