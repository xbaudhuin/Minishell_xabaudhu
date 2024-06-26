/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:22:14 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/06 14:53:03 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quotes(const char c)
{
	if (c == '\'')
	{
		return (SIMPLE_QUOTES);
	}
	if (c == '"')
	{
		return (DOUBLE_QUOTES);
	}
	return (FALSE);
}

int	is_parenthesis(const char c)
{
	if (c == '(')
	{
		return (PARENTHESIS_OPEN);
	}
	if (c == ')')
	{
		return (PARENTHESIS_CLOSE);
	}
	return (FALSE);
}

int	is_redirection(const char c)
{
	if (c == '>')
		return (REDIRECT_OUT);
	if (c == '<')
		return (REDIRECT_IN);
	return (FALSE);
}

int	is_operator(const char c)
{
	if (c == '&')
		return (AND);
	if (c == '|')
		return (PIPE);
	return (FALSE);
}

int	is_dollar_char(const char c)
{
	if (ft_isalnum(c) == 1)
		return (TRUE);
	if (c == '_')
		return (TRUE);
	return (FALSE);
}
