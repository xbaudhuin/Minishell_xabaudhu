/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:18:01 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/28 18:43:46 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->len_word = 0;
	token->word = NULL;
	token->next = NULL;
	token->depths = 0;
	token->type = 0;
	token->previous = NULL;
	return (token);
}

static t_token	*ft_token_last(t_token *token)
{
	if (token)
	{
		while (token->next)
			token = token->next;
		return (token);
	}
	return (NULL);
}

void	ft_token_add_back(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (head != NULL)
	{
		if (*head != NULL)
		{
			tmp = ft_token_last(*head);
			tmp->next = new;
			new->previous = tmp;
		}
		else
			*head = new;
	}
}

t_token	*add_back_redirect(t_command *cmd, t_token *token)
{
	t_token	*tmp_next;

	tmp_next = token->next;
	token->next = NULL;
	token->previous = NULL;
	if (tmp_next != NULL)
		tmp_next->previous = NULL;
	ft_token_add_back(&cmd->redirect_token, token);
	return (tmp_next);
}

t_token	*add_back_word(t_command *cmd, t_token *token)
{
	t_token	*tmp_next;

	tmp_next = token->next;
	token->next = NULL;
	token->previous = NULL;
	if (tmp_next != NULL)
		tmp_next->previous = NULL;
	ft_token_add_back(&cmd->token, token);
	return (tmp_next);
}
