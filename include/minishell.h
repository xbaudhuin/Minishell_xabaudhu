/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:10:44 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/26 17:23:31 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "environment.h"
# include "builtins.h"
# include "get_next_line.h"
# include "ft_printf.h"

#define RESET  "\x1B[0m"
#define RED "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <strings.h>
# include <errno.h>
//# include <stropts.h>
//# include <termcap.h>

# define SUCCESS 0
# define FAILURE 1

# define FALSE 0
# define TRUE 1
# define PARSE_ERROR 2

# define NO_QUOTES 0

enum e_flag
{
	EMPTY = 0,
	SIMPLE_QUOTES = 1,
	DOUBLE_QUOTES = 2,
	AND_OPERATOR,
	PIPE_OPERATOR,
};

enum e_node
{
	NODE_ERROR = 0,
	NODE_ROOT = 1,
	NODE_LEAF = 2,
	NODE_AND = 3,
	NODE_OR = 4,
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
	HERE_DOC_NO_EXPAND = 9,
	REDIRECT_OUT = 10,
	APPEND_OUT = 11,
};

typedef int (*t_is_valid_type)(int);

typedef struct s_token
{
	int				type;
	char			*word;
	unsigned int	len_word;
	unsigned int	depths;
	struct s_token	*previous;
	struct s_token	*next;
}			t_token;

typedef struct s_command
{
	t_token	*token;
	char	**argv;
	t_token	*redirect_token;
}			t_command;

typedef struct s_node
{
	t_command		**cmd;
	int				exit_status;
	int				type;
	struct s_node	*left_node;
	struct s_node	*right_node;
	struct s_node	*parent_node;
}			t_node;

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
void			ft_del_token(t_token *token);
//Here_doc

int	is_here_doc(const int previous_type, const int current_type);
void	do_here_doc(t_token *here_doc, t_token **head);
unsigned int	go_to_next_quotes(const char *str, char quotes);
//error_handling
void			ft_parse_error(const char *message);
//Handle signal

int				handle_sigquit(int ignore);
int				handle_sigint(int new_prompt);

int				is_word_token(int type);
int				is_operator_token(int type);
int				is_parenthesis_token(const int type);
int				is_redirect_token(int type);
int				early_valid_type(int type);
int				previous_word_token(const int type);
int				previous_operator_token(const int type);
int				previous_parenthesis_close_token(const int type);
int				previous_type_error(const int type);

int				check_token_list(t_token **head);
void			simplify_token_list(t_token **head);
t_command		**create_command_array(t_token *token, int *error);
t_node			*create_node(t_token **head, int type, int *error);
int				create_tree(t_token **head, t_node **node, int *error);
void			free_tree(t_node **root);
void			free_t_command(t_command **cmd);
void			print_tree(t_node **root, int id);

#endif
