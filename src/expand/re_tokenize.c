/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:06:42 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/08 12:32:58 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static int	filltoken_word(
	const char *buf, t_token *token, unsigned int *index, int type)
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
	token->type = type;
	token->word = token_dup_word(buf, i, token);
	if (token->word == NULL)
	{
		ft_del_token(token);
		return (FAILURE);
	}
	*index += i;
	return (SUCCESS);
}

static void	add_back_list(t_token *token, t_token *new_token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_token;
	new_token->previous = tmp;
}

static void	insert_mid_list(t_token *token, t_token *save_next)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = save_next;
	if (save_next != NULL)
		save_next->previous = tmp;
}

static int	create_new_token(const char *buf, t_token *token, int type)
{
	unsigned int	i;
	t_token			*new_token;

	i = 0;
	while (buf[i] != '\0')
	{
		i += skip_spaces(&buf[i]);
		if (buf[i] == '\0')
			break ;
		new_token = init_token();
		if (new_token == NULL)
		{
			perror(RED"expand re_tokenize"RESET);
			return (FAILURE);
		}
		if (filltoken_word(&buf[i], new_token, &i, type) == FAILURE)
			return (FAILURE);
		add_back_list(token, new_token);
	}
	return (SUCCESS);
}

int	re_tokenize(t_token *token)
{
	unsigned int	i;
	t_token			*save_next;
	char			*buf;
	int				type;

	buf = token->word;
	type = token->type;
	token->word = NULL;
	save_next = token->next;
	token->next = NULL;
	i = 0;
	if (filltoken_word(buf, token, &i, type) == FAILURE)
		return (free(buf), FAILURE);
	i += skip_spaces(&buf[i]);
	if (is_redirect_token(token->type) == TRUE && buf[i] != '\0')
		token->type = ERROR;
	else if (create_new_token(&buf[i], token, type) == FAILURE)
		return (free(buf), FAILURE);
	free(buf);
	insert_mid_list(token, save_next);
	return (SUCCESS);
}
