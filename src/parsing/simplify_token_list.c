/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify_token_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:48:00 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/28 19:19:34 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*remove_parenthesis(t_token **head, t_token *token_parenthesis)
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

static t_token	*concatenate_redirect_token(t_token **head, t_token *redirect)
{
	t_token	*next;

	if (is_here_doc_token(redirect->type) == TRUE)
		return (redirect->next);
	next = redirect->next->next;
	if (redirect->previous == NULL)
	{
		redirect->next->type = redirect->type;
		(*head) = redirect->next;
		ft_del_token(redirect);
		return (next);
	}
	redirect->previous->next = redirect->next;
	redirect->next->type = redirect->type;
	ft_del_token(redirect);
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

t_token	*remove_pipe(t_token *pipe)
{
	t_token	*next_token;

	next_token = pipe->next;
	if (next_token != NULL)
		next_token->previous = NULL;
	ft_del_token(pipe);
	return (next_token);
}
