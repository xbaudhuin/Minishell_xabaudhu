/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:17:31 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/06 18:28:02 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	skip_dollar(const char *word)
{
	unsigned int	i;

	i = 0;
	if (word[i] == '$')
		return (0);
	if (word[i] == '?')
		return (1);
	while (is_dollar_char(word[i]) == TRUE)
		i++;
	return (i);
}

int	is_dollar_expandable(const char *word)
{
	unsigned int	i;
	int				flag_quotes;

	i = 0;
	flag_quotes = FALSE;
	if (word == NULL)
		return (FALSE);
	while (word[i] != '\0')
	{
		if (word[i] == '\'')
		{
			if (flag_quotes == FALSE)
				flag_quotes = TRUE;
			else
				flag_quotes = TRUE;
		}
		if (word[i] == '$' && flag_quotes == FALSE)
			return (TRUE);
		else
			i++;
	}
	return (FALSE);
}

int	expand_dollar_list(t_token **head, const t_env env)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (is_dollar_expandable(tmp->word) == TRUE)
		{
			tmp->word = do_dollar_expansion(tmp->word, env);
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

int	expand_dollar(t_command **cmd, const t_env env)
{
	unsigned int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->token)
		{
			if (expand_dollar_list(&cmd[i]->token, env) == FAILURE)
				return (FAILURE);
		}
		if (cmd[i]->redirect_token)
		{
			if (expand_dollar_list(&cmd[i]->redirect_token, env) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
