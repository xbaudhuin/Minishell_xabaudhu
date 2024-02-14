/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:22:14 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/14 15:11:25 by xabaudhu         ###   ########.fr       */
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
	return(FALSE);
}

int	is_redirection(const char c)
{
	if (c == '>')
		return (OUT_REDIRECTION);
	if (c == '<')
		return (IN_REDIRECTION);
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

int	is_portable_char(const char c)
{
	if (c == 0)
		return (TRUE);
	if (c >=7 && c <= 13)
		return (TRUE);
	if (c >= 32 && c <= 126)
		return (TRUE);
	return (FALSE);
}
