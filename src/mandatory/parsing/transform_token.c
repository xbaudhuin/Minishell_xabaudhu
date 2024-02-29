/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:50:13 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/29 15:02:23 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	transform_pipe(t_token *token)
{
	if (token->len_word >= 3)
		token->type = ERROR;
	if (token->len_word == 2)
		token->type = OR;
}

static void transform_redirect(t_token *token)
{
	if (token->type == REDIRECT_IN)
	{
		if (token->len_word >= 3)
			token->type = ERROR;
		if (token->len_word == 2)
			token->type = HERE_DOC;
	}
	if (token->type == REDIRECT_OUT)
	{
		if (token->len_word >= 3)
			token->type = ERROR;
		if (token->len_word == 2)
			token->type = APPEND_OUT;
	}
}

void	transform_token(t_token *token)
{
	if (token->type == PIPE)
		transform_pipe(token);
	if (token->type == AND)
	{
		if (token->len_word != 2)
			token->type = ERROR;
	}
	if (is_redirect_token(token->type)== TRUE)
		transform_redirect(token);
}
