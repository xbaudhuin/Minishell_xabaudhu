/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:17:31 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/08 17:06:13 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

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

int	is_dollar_expandable(const char *word, const int type)
{
	unsigned int	i;
	char			flag_quotes;

	i = 0;
	flag_quotes = FALSE;
	if (word == NULL || is_here_doc_token(type) == TRUE)
		return (FALSE);
	while (word[i] != '\0')
	{
		if (is_quotes(word[i]))
		{
			if (flag_quotes == FALSE)
				flag_quotes = word[i];
			else if (flag_quotes == word[i])
				flag_quotes = FALSE;
		}
		if (word[i] == '$' && flag_quotes != '\'')
			return (TRUE);
		else
			i++;
	}
	return (FALSE);
}

static t_token	*ft_remove_one_from_list(t_token *token, t_token **head)
{
	t_token	*previous;
	t_token	*next;

	previous = token->previous;
	next = token->next;
	if (previous != NULL)
		previous->next = next;
	if (next != NULL)
		next->previous = previous;
	if (*head == token)
		(*head) = next;
	ft_del_token(token);
	return (NULL);
}

int	expand_dollar_list(t_token **head, const t_env env)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (is_dollar_expandable(tmp->word, tmp->type) == TRUE)
		{
			tmp->word = do_dollar_expansion(tmp->word, env);
			if (tmp->word == NULL)
				return (free_token(head), FAILURE);
			if (tmp->word[0] == '\0')
				tmp = ft_remove_one_from_list(tmp, head);
			else if (re_tokenize(tmp) == FAILURE)
				return (free_token(head), FAILURE);
		}
		if (tmp == NULL)
			break ;
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
