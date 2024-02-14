/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:34:58 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/14 18:03:58 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_printf.h"
#include "string.h"
//read_line rl_clear_history rl_on_new_line
//rl_replace_line rl_redisplay, add_history


//character special () && || | $ * "" '' $? >> > << < 'espace outside quotes'
// dollar seul = '$'

static void	init_flag(t_flag *flag)
{
	flag->double_quotes = FALSE;
	flag->simple_quotes = FALSE;
	flag->parenthesis_open = FALSE;
	flag->parenthesis_close = FALSE;
	flag->operator = TRUE;
	flag->redirection = FALSE;
}
/*
int	fill_token(const char *buf, t_token **head, t_flag *flag)
{
	t_token		*token;
	unsigned int	i;

	i = 0;
	if (is_parenthesis(buf[i], flag) == TRUE)
	{
		token = token_parenthesis(buf[i], flag);
	}
	else if (is_quotes(buf[i], flag) == TRUE)
	{
		token = token_quotes(&buf[i], buf[i], flag);
	}
	else if (is_operator(buf[i], flag) == TRUE)
	{
		token = token_operator(&buf[i], buf[i], flag);
	}
	else if (is_redirection(buf[i]) == TRUE)
	{
		token = token_redirection(&buf[i], buf[i], flag);
	}
	else if (is_)


}
*/

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

int	fill_token(const char *buf, t_token *token)
{
	unsigned int	i;
	t_flag			flag;

	i = 0;
	init_flag(&flag);
	while (buf[i])
	{
		if (get_type_token(buf[i]) != token->type)
			break ;
		if (is_quotes(buf[i]))
		i++;
	}
	token->len_word = i;
	token->word = ft_strndup(buf, i);
	if (token->word == NULL)
		return (FAILURE);

}


t_token	*get_current_token(const char *buf, int *index_buf)
{
	unsigned int	i;
	int				type;
	t_token			*token;

	i = 0;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = get_type_token(buf[i]);
	fill_token(buf, token);

}

char	*parse_to_token(const char *buf)
{
	unsigned int	i;
	t_flag			flag;
	t_token			*token;
	t_token			**head;
	int				previous_type;

	i = 0;
	previous_type = EMPTY;
	while (buf[i])
	{
		i += skip_space(buf);
		token = get_current_token(&buf[i], , &i);

	}
}

void	ft_readline(void)
{
	char	*buf;

	while (1)
	{
		buf =  readline("minishell> ");
		if (!buf)
			return ;
		if (ft_strlen(buf) > 0)
			add_history(buf);
		parse_to_token(buf);
		free(buf);
	}
	rl_clear_history();
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	ft_readline();
	return (0);
}

