/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_token_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:10:44 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/28 20:55:25 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_type_token(const char c)
{
	int	type;

	type = FALSE;
	type = is_parenthesis(c);
	if (type != FALSE)
		return (type);
	type = is_redirection(c);
	if (type != FALSE)
		return (type);
	type = is_operator(c);
	if (type != FALSE)
		return (type);
	return (WORD);
}

static unsigned int	go_to_next_quotes_index(const char *buf, int *flag_quotes)
{
	unsigned int	i;
	char			quotes;

	i = 0;
	quotes = buf[i];
	*flag_quotes += 1;
	i++;
	while (buf[i] != '\0')
	{
		if (buf[i] == quotes)
		{
			*flag_quotes -= 1;
			break ;
		}
		i++;
	}
	return (i);
}

int	fill_token(const char *buf, t_token *token, unsigned int *index_buf)
{
	unsigned int	i;
	int				flag_quotes;

	i = 0;
	flag_quotes = 0;
	while (buf[i] != '\0')
	{
		if (i >= 1 && (token->type == PARENTHESIS_CLOSE
				|| token->type == PARENTHESIS_OPEN))
			break ;
		if (get_type_token(buf[i]) != token->type
			|| ft_is_space(buf[i]) == TRUE)
			break ;
		if (is_quotes(buf[i]))
			i += go_to_next_quotes_index(&buf[i], &flag_quotes) + 1;
		else
			i++;
	}
	if (flag_quotes >= 1)
		token->type = ERROR;
	*index_buf += i;
	token->word = token_dup_word(buf, i, token);
	if (token->word == NULL)
		return (FAILURE);
	return (SUCCESS);
}
