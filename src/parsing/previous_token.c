/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   previous_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:00:39 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/07 13:57:31 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	early_valid_type(const int type)
{
	if (type == HERE_DOC_TOKEN)
		return (FALSE);
	if (is_redirect_token(type) == TRUE)
		return (TRUE);
	if (is_word_token(type) == TRUE)
		return (TRUE);
	if (type == PARENTHESIS_OPEN)
		return (TRUE);
	if (is_here_doc_token(type) == TRUE)
		return (TRUE);
	return (FALSE);
}

int	previous_word_token(const int type)
{
	if (is_word_token(type) == TRUE)
		return (TRUE);
	if (is_redirect_token(type) == TRUE)
		return (TRUE);
	if (type == PARENTHESIS_CLOSE)
		return (TRUE);
	if (is_operator_token(type) == TRUE)
		return (TRUE);
	if (is_here_doc_token(type) == TRUE)
		return (TRUE);
	return (FALSE);
}

int	previous_operator_token(const int type)
{
	if (is_word_token(type) == TRUE)
		return (TRUE);
	if (type == PARENTHESIS_OPEN)
		return (TRUE);
	if (is_redirect_token(type) == TRUE)
		return (TRUE);
	return (FALSE);
}

int	previous_parenthesis_close_token(const int type)
{
	if (is_redirect_token(type) == TRUE)
		return (TRUE);
	if (is_operator_token(type) == TRUE)
		return (TRUE);
	if (type == PARENTHESIS_CLOSE)
		return (TRUE);
	return (FALSE);
}

int	previous_type_error(const int type)
{
	(void)type;
	return (FALSE);
}
