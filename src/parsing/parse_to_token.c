/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:47:25 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/11 16:11:35 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token_type_error(const int type)
{
	if (type == ERROR)
		return (TRUE);
	if (type == FAIL_DUP)
		return (TRUE);
	if (type == FAIL_MALLOC)
		return (TRUE);
	return (FALSE);
}

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

static t_token	**parse_token_error(t_token **head, t_token *token, t_env *env)
{
	if (token && (token->type == ERROR || token->type == FAIL_DUP))
	{
		env->exit_status = 2;
		ft_fprintf(2, RED "minishell: "
			"syntax error near unexpected token"RESET" %s\n", token->word);
		ft_del_token(token);
	}
	else if (token != NULL && token->type == HERE_DOC_TOKEN)
	{
		env->exit_status = 2;
		ft_fprintf(2, RED "minishell: "
			"syntax error near unexpected token"RESET" %s\n", token->word);
	}
	else if (token == NULL || token->type == FAIL_MALLOC)
		env->exit_status = 139;
	free_token(head);
	return (NULL);
}

static int	launch_here_doc(t_token *token, t_token **head, int *previous_type)
{
	if (*previous_type != HERE_DOC_TOKEN)
		return (SUCCESS);
	if (is_here_doc(*previous_type, token->type) == FALSE)
	{
		token->type = HERE_DOC_TOKEN;
		return (FAILURE);
	}
	do_here_doc(token, head, previous_type);
	return (SUCCESS);
}

t_token	**parse_to_token(const char *buf, t_token **head, t_env *env)
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
		if (token == NULL || is_token_type_error(token->type) == TRUE)
			return (parse_token_error(head, token, env));
		ft_token_add_back(head, token);
		if (launch_here_doc(token, head, &previous_type) == FAILURE)
			return (parse_token_error(head, token, env));
		else
			previous_type = token->type;
		if (token == NULL || is_token_type_error(token->type) == TRUE)
			return (parse_token_error(head, NULL, env));
	}
	return (head);
}
