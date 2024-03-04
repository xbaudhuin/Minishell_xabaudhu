/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:06:42 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/04 19:41:44 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_token_word(const char *buf, t_token *token, unsigned int *index)
{
	unsigned int	i;
	int				flag_quotes;

	i = 0;
	flag_quotes = FALSE;
	while (buf[i] != '\0')
	{
		if (ft_is_space(buf[i]) == TRUE)
			break ;
		if (is_quotes(buf[i]))
			i += go_to_next_quotes(&buf[i + 1], buf[i]) + 1;
		else
			i++;
	}
	token->type = WORD;
	token->word = token_dup_word(buf, i, token);
	if (token->word == NULL)
	{
		ft_del_token(token);
		return (FAILURE);
	}
	*index += i;
	return (SUCCESS);
}

static void	insert_mid_list(t_token *token, t_token *new_token)
{
	t_token	*next_token;

	next_token = token->next;
	new_token->next = next_token;
	token->next = new_token;
	new_token->previous = token;
	if (next_token != NULL)
	{
		next_token->previous = new_token;
	}
}

int	re_tokenize(t_token *token)
{
	unsigned int	i;
	t_token			*new_token;
	char			*buf;

	buf = token->word;
	token->word = NULL;
	i = 0;
	if (fill_token_word(buf, token, &i) == FAILURE)
		return (free(buf), FAILURE);
	while (buf[i] != '\0')
	{
		i += skip_spaces(&buf[i]);
		if (buf[i] == '\0')
			break ;
		new_token = init_token();
		if (new_token == NULL)
		{
			perror(RED"expand re_tokenize"RESET);
			return (free(buf), FAILURE);
		}
		if (fill_token_word(&buf[i], new_token, &i) == FAILURE)
			return (free(buf), FAILURE);
		insert_mid_list(token, new_token);
	}
	free(buf);
	return (SUCCESS);
}

