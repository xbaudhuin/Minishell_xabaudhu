/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:34:58 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/16 12:30:15 by xabaudhu         ###   ########.fr       */
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

/*static void	init_flag(t_flag *flag)
{
	flag->double_quotes = FALSE;
	flag->simple_quotes = FALSE;
	flag->parenthesis_open = FALSE;
	flag->parenthesis_close = FALSE;
	flag->operator = TRUE;
	flag->redirection = FALSE;
}*/
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

char	*smart_tokenndup(const char *buf, const unsigned int len_buf, t_token *token)
{
	unsigned int	i;
	unsigned int	j;
	char			*word;
	char			quotes;

	i = 0;
	j = 0;
	quotes = '\0';
	word = malloc(sizeof(*word) * (token->len_word + 1));
	if (!word)
		return (NULL);
	while (i < len_buf)
	{
		if (is_quotes(buf[i]))
		{
			if (quotes == '\0')
			{
				quotes = buf[i];
				i++;
			}
			else if (quotes == buf[i])
			{
				quotes = '\0';
				i++;
			}
			else
			{
				word[j] = buf[i];
				i++;
				j++;
			}
		}/*
		else if (buf[i] == '$')
		{
			if (quotes == '\0' || quotes == '"')
			{
				while (buf[i] && buf[i] != ' ')
				{
					word[j] = buf[i];
					j++;
					i++;
				}
				word[j] = '\\';
				j++;
			}
			else
		}*/
		else
		{
			word[j] = buf[i];
			i++;
			j++;
		}
	}
	word[j] = '\0';
	token->len_word = j;
	if (quotes != '\0')
		token->type = ERROR;
	return (word);
}

int	go_to_next_quotes(const char *buf, unsigned int *add_special)
{
	unsigned int	i;
	char			quotes;

	i = 0;
	quotes = buf[i];
	i++;
	while (buf[i] && buf[i] != quotes)
	{
		if (buf[i] == '$' || buf[i] == '\\')
			*add_special += 1;
		i++;
	}
	return (i);
}

int	fill_token(const char *buf, t_token *token, unsigned int *index_buf)
{
	unsigned int	i;
	unsigned int	add_special;

	i = 0;
	add_special = 0;
	while (buf[i])
	{
		if (i >= 1 && (token->type == PARENTHESIS_CLOSE || token->type == PARENTHESIS_OPEN))
			break ;
		if (get_type_token(buf[i]) != token->type || buf[i] == ' ')
			break ;
		if (is_quotes(buf[i]))
			i += go_to_next_quotes(&buf[i], &add_special);
		if (buf[i] == '$' || buf[i] == '\\')
			add_special++;
		i++;
	}
	*index_buf += i;
	token->len_word = i + add_special;
	token->word = smart_tokenndup(buf, i, token);
	if (token->word == NULL)
		return (FAILURE);
	return (SUCCESS);
}

void	transform_token(t_token *token)
{
	if (token->type == PIPE)
	{
		if (token->len_word >= 3)
			token->type = ERROR;
		if (token->len_word == 2)
			token->type = OR;
	}
	if (token->type == AND)
	{
		if (token->len_word != 2)
			token->type = ERROR;
	}
	if (token->type == REDIRECT_IN)
	{
		if (token->len_word >= 3)
			token->type = ERROR;
		if (token->len_word == 2)
			token->type = HERE_DOC;
	}
	if (token->type == REDIRECT_OUT)
	{
		if (token->len_word >= 3)
			token->type = ERROR;
		if (token->len_word == 2)
			token->type = APPEND_OUT;
	}
}

t_token	*get_current_token(const char *buf, unsigned int *index_buf)
{
	unsigned int	i;
	t_token			*token;

	i = 0;
	token = init_token();
	if (!token)
		return (NULL);
	token->type = get_type_token(buf[i]);
	if (fill_token(buf, token, index_buf) == FAILURE)
	{
		ft_fprintf(2, RED "Fail malloc\n" RESET);
		free(token);
		return (NULL);
	}
	transform_token(token);
	return (token);
}

t_token	**parse_to_token(const char *buf, t_token **head)
{
	unsigned int	i;
	t_token			*token;

	i = 0;
	while (buf[i])
	{
		i += skip_spaces(&buf[i]);
		token = get_current_token(&buf[i], &i);
		if (!token)
		{
			free_token(head);
			return (NULL);
		}
		if (token->type == ERROR)
		{
			ft_fprintf(2, RED "minishell: syntax error near unexpected token %s\n" RESET, token->word);
			free_token(head);
			return (NULL);
		}
		ft_token_add_back(head, token);
	}
	return (head);
}

void	ft_readline(void)
{
	char	*buf;
	t_token	*head;

	while (1)
	{
		buf =  readline("minishell> ");
		if (!buf)
			return ;
		if (ft_strlen(buf) > 0)
			add_history(buf);
		parse_to_token(buf, &head);
		print_token(&head);
		free_token(&head);
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

