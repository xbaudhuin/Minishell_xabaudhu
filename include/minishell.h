/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:10:44 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/15 18:04:00 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>

#define RESET  "\x1B[0m"
#define RED "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"

# define SUCCESS 0
# define FAILURE 1

# define FALSE 0
# define TRUE 1
# define PARSE_ERROR 2

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
	ERROR = 0,
	PARENTHESIS_OPEN = 1,
	PARENTHESIS_CLOSE = 2,
	WORD = 3,
	PIPE = 4,
	AND = 5,
	OR = 6,
	REDIRECT_IN = 7,
	HERE_DOC = 8,
	REDIRECT_OUT = 9,
	APPEND_OUT = 10,
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
void			ft_token_add_back(t_token **head, t_token *new);
t_token			*init_token(void);
void			print_token(t_token **head);
void			free_token(t_token **head);

#endif
