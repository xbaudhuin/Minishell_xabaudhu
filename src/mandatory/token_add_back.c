/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:18:01 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/23 18:55:16 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"

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
