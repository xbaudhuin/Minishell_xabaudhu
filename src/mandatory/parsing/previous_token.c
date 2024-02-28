/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   previous_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:00:39 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/28 18:08:01 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	early_valid_type(const int type)
{
	if (is_redirect_token(type) == TRUE)
		return (TRUE);
	if (is_word_token(type) == TRUE)
		return (TRUE);
	if (type == PARENTHESIS_OPEN)
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
