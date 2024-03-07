/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:51:02 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/07 13:52:15 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator_token(const int type)
{
	if (type == PIPE)
		return (TRUE);
	if (type == AND)
		return (TRUE);
	if (type == OR)
		return (TRUE);
	return (FALSE);
}

int	is_redirect_token(const int type)
{
	if (type == REDIRECT_IN)
		return (TRUE);
	if (type == HERE_DOC_TOKEN)
		return (TRUE);
	if (type == REDIRECT_OUT)
		return (TRUE);
	if (type == APPEND_OUT)
		return (TRUE);
	return (FALSE);
}

int	is_word_token(const int type)
{
	if (type == WORD)
		return (TRUE);
	return (FALSE);
}

int	is_parenthesis_token(const int type)
{
	if (type == PARENTHESIS_CLOSE)
		return (TRUE);
	if (type == PARENTHESIS_OPEN)
		return (TRUE);
	return (FALSE);
}

int	is_here_doc_token(const int type)
{
	if (type == HERE_DOC)
		return (TRUE);
	if (type == HERE_DOC_NO_EXPAND)
		return (TRUE);
	return (FALSE);
}
