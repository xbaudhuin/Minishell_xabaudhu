/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:23:19 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/13 18:25:06 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"


# define PARSE_ERROR 2
# define IN_REDIRECTION -1
# define OUT_REDIRECTION 1

enum e_flag
{
	EMPTY = 0,
	SIMPLE_QUOTES = 1,
	DOUBLE_QUOTES = 2,
	AND_OPERATOR,
	PIPE_OPERATOR,
};

enum e_type_token
{
	PARENTHESIS_OPEN = 1,
	PARENTHESIS_CLOSE,
	WORD,
	PIPE,
	AND,
	OR,
	REDIRECT_IN,
	HERE_DOC,
	REDIRECT_OUT,
	APPEND_OUT,
};

typedef struct s_token
{
	int				type;
	char			*word;
	unsigned int	len_word;
	struct s_token	*inside_token;
	struct s_token	*next;
}			t_token;

typedef struct	s_flag
{
	int	simple_quotes;
	int	main_quotes;
	int	parenthesis_open;
	int	parenthesis_close;
	int	double_quotes;
	int	redirection;
	int	operator;
}				t_flag;


//check if special char

unsigned int	skip_spaces(const char *buf);
int				is_quotes(const char c);
int				is_parenthesis(const char c);
int 			is_operator(const char c);
int				is_redirection(const char c);

#endif
