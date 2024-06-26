/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special_char2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:25:12 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/11 15:34:08 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_opening_flag(const char c)
{
	if (c == '(' || c == '"' || c == '\'')
		return (TRUE);
	return (FALSE);
}

int	ft_is_space(const char c)
{
	if (c == ' ')
		return (TRUE);
	if (c == 9)
		return (TRUE);
	if (c == '\n')
		return (TRUE);
	return (FALSE);
}

unsigned int	skip_spaces(const char *buf)
{
	unsigned int	i;

	i = 0;
	while (ft_is_space(buf[i]) == TRUE)
		i++;
	return (i);
}

int	is_dollar_quotes(const char c, const char quotes)
{
	if (is_dollar_char(c) == FALSE)
	{
		if (is_quotes(c) == FALSE || (quotes == '"'))
			return (FALSE);
	}
	return (TRUE);
}
