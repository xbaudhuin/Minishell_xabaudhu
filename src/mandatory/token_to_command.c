/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:15:17 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/21 15:16:25 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	previous_pipe_token(const int type)
{
	if (is_word_token(type) == TRUE)
		return (TRUE);
	if (is_redirect_token(type)== TRUE)
		return (TRUE);
	return (FALSE);
}

static int	check_parenthesis_flag(const int type, int *flag)
{
	if (type == PARENTHESIS_OPEN)
		*flag += 1;
	if (type == PARENTHESIS_CLOSE)
		*flag -=1;
	if (*flag < 0)
		return (FALSE);
	return (TRUE);
}

static int	check_last_token(const int type, int flag, int (*is_valid_type)(int))
{
	if (is_valid_type(type) == FALSE)
		return (FALSE);
	if (flag != 0)
		return (FALSE);
	if (type == PARENTHESIS_CLOSE)
		return (TRUE);
	if (is_word_token(type) == TRUE)
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
	return (&previous_type_error);
}

int	check_token_list(const t_token **head)
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
		if (is_valid_type(tmp_token->type) == FALSE)
			break ;
		if (tmp_token->next == NULL)
			break ;
		tmp_token->depths = flag;
		is_valid_type = get_new_valid_type(tmp_token->type);
		tmp_token = tmp_token->next;
	}
	if (tmp_token->next != NULL || check_last_token(tmp_token->type, flag, is_valid_type) == FALSE)
	{
		ft_fprintf(2, RED "minishell: parse error near: '%s'\n" RESET, tmp_token->word);
		return (FALSE);
	}
	return (TRUE);
}
