/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify_token_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:48:00 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/26 12:28:10 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*remove_parenthesis(t_token **head, t_token *token_parenthesis)
{
	t_token	*next;

	next = token_parenthesis->next;
	if (token_parenthesis->previous == NULL)
	{
		(*head) = token_parenthesis->next;
		(*head)->previous = NULL;
	}
	else
	{
		token_parenthesis->previous->next = next;
		if (token_parenthesis->next != NULL)
			token_parenthesis->next->previous = token_parenthesis->previous;
	}
	ft_del_token(token_parenthesis);
	return (next);
}

t_token	*concatenate_redirect_token(t_token **head, t_token *token_redirect)
{
	t_token	*next;

	if (token_redirect->type == HERE_DOC || token_redirect->type == HERE_DOC_NO_EXPAND)
		return (token_redirect->next);
	next = token_redirect->next->next;
	if (token_redirect->previous == NULL)
	{
		token_redirect->next->type = token_redirect->type;
		(*head) = token_redirect->next;
		ft_del_token(token_redirect);
		return (next);
	}
	token_redirect->previous->next = token_redirect->next;
	token_redirect->next->type = token_redirect->type;
	ft_del_token(token_redirect);
	return (next);
}

void	simplify_token_list(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (is_parenthesis_token(tmp->type) == TRUE)
		{
			tmp = remove_parenthesis(head, tmp);
		}
		else if (is_redirect_token(tmp->type) == TRUE)
		{
			tmp = concatenate_redirect_token(head, tmp);
		}
		else
		{
			tmp = tmp->next;
		}
	}
}
