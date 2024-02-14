/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:10:44 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/14 15:37:26 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>

# define SUCCESS 0
# define FAILURE 1

# define FALSE 0
# define TRUE 1
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
	//struct s_token	*inside_token;
	struct s_token	*next;
}			t_token;

typedef struct s_command
{
	char	**args;
	int		fd[2];
}			t_command;

typedef struct	s_flag
{
	int	simple_quotes;
	int	main_quotes;
	int	parenthesis_open;
	int	parenthesis_close;
	int	double_quotes;
	int	redirection;
	int	operator;
	int	error;
}				t_flag;

typedef struct s_command_node
{
	t_command				*command;
	int						nb_command;
	int						fork;
	struct s_command_node	*left_node;
	struct s_command_node	*right_node;
	struct s_command_node	*parent_node;
}			t_command_node;

//check if special char

int				ft_is_space(const char c);
unsigned int	skip_spaces(const char *buf);
int				is_quotes(const char c);
int				is_parenthesis(const char c);
int 			is_operator(const char c);
int				is_redirection(const char c);

#endif
