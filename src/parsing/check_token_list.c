/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:15:17 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/07 13:58:30 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static int	check_parenthesis_flag(const int type, int *flag)
{
	if (type == PARENTHESIS_OPEN)
		*flag += 1;
	if (type == PARENTHESIS_CLOSE)
		*flag -= 1;
	if (*flag < 0)
		return (FALSE);
	return (TRUE);
}

static int	check_lasttoken(const int type, int flag, int (*is_valid_type)(int))
{
	if (is_valid_type(type) == FALSE)
		return (FALSE);
	if (flag != 0)
		return (FALSE);
	if (type == PARENTHESIS_CLOSE)
		return (TRUE);
	if (is_word_token(type) == TRUE)
		return (TRUE);
	if (is_here_doc_token(type) == TRUE)
		return (TRUE);
	return (FALSE);
}

static t_is_valid_type	get_new_valid_type(const int type)
{
	if (type == PIPE)
		return (&previous_pipe_token);
	if (is_redirect_token(type) == TRUE)
		return (&is_word_token);
	if (is_word_token(type) == TRUE)
		return (&previous_word_token);
	if (is_operator_token(type) == TRUE)
		return (&previous_operator_token);
	if (type == PARENTHESIS_OPEN)
		return (&early_valid_type);
	if (type == PARENTHESIS_CLOSE)
		return (&previous_parenthesis_close_token);
	if (is_here_doc_token(type) == TRUE)
		return (&previous_word_token);
	return (&previous_type_error);
}

static int	error_parsing_token(t_token **head, const char *word)
{
	ft_fprintf(2, RED "minishell: parse error near: "RESET"'%s'\n", word);
	free_token(head);
	return (FALSE);
}

int	check_token_list(t_token **head)
{
	int				(*is_valid_type)(int);
	t_token			*tmp_token;
	int				flag;

	flag = 0;
	tmp_token = (t_token *)*head;
	is_valid_type = early_valid_type;
	while (tmp_token != NULL)
	{
		if (check_parenthesis_flag(tmp_token->type, &flag) == FALSE)
			break ;
		if (is_valid_type(tmp_token->type) == FALSE || tmp_token->next == NULL)
			break ;
		tmp_token->depths = flag;
		is_valid_type = get_new_valid_type(tmp_token->type);
		tmp_token = tmp_token->next;
	}
	if (tmp_token->next != NULL
		|| check_lasttoken(tmp_token->type, flag, is_valid_type) == FALSE)
		return (error_parsing_token(head, tmp_token->word));
	simplify_token_list(head);
	return (TRUE);
}
