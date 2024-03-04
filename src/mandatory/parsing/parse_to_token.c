/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:47:25 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/01 16:52:23 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*get_current_token(const char *buf, unsigned int *index_buf)
{
	unsigned int	i;
	t_token			*token;

	i = 0;
	token = init_token();
	if (token == NULL)
		return (NULL);
	token->type = get_type_token(buf[i]);
	if (fill_token(buf, token, index_buf) == FAILURE)
	{
		perror(RED"get_current_token"RESET);
		free(token);
		return (NULL);
	}
	transform_token(token);
	return (token);
}

static t_token	**parse_token_error(t_token **head, t_token *token)
{
	if (token && token->type == ERROR)
	{
		ft_fprintf(2, RED "minishell: "
			"syntax error near unexpected token %s\n" RESET, token->word);
		ft_del_token(token);
	}
	free_token(head);
	return (NULL);
}

t_token	**parse_to_token(const char *buf, t_token **head)
{
	unsigned int	i;
	t_token			*token;
	int				previous_type;

	i = 0;
	previous_type = ERROR;
	while (buf[i])
	{
		i += skip_spaces(&buf[i]);
		if (buf[i] == '\0')
			break ;
		token = get_current_token(&buf[i], &i);
		if (token == NULL || token->type == ERROR)
			return (parse_token_error(head, token));
		ft_token_add_back(head, token);
		if (is_here_doc(previous_type, token->type) == TRUE)
			do_here_doc(token, head, &previous_type);
		else
			previous_type = token->type;
	}
	return (head);
}
