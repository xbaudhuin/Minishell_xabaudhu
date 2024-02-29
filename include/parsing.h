/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:51:16 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/29 15:01:36 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structures.h"
// is char function

int				is_quotes(const char c);
int				is_parenthesis(const char c);
int				is_redirection(const char c);
int				is_operator(const char c);
int				is_end_dollar_char(const char c);
int				is_opening_flag(const char c);
int				ft_is_space(const char c);

// is token function

int				is_operator_token(const int type);
int				is_redirect_token(const int type);
int				is_word_token(const int type);
int				is_parenthesis_token(const int type);
int				is_here_doc_token(const int type);
int				get_type_token(const char c);

// previous_token function

int				early_valid_type(const int type);
int				previous_word_token(const int type);
int				previous_operator_token(const int type);
int				previous_parenthesis_close_token(const int type);
int				previous_type_error(const int type);
int				previous_pipe_token(const int type);
int				is_here_doc(const int previous_type, const int current_type);

// t_token list function

t_token			*init_token(void);
void			ft_token_add_back(t_token **head, t_token *new);
int				check_token_list(t_token **head);
void			simplify_token_list(t_token **head);
t_token			*remove_pipe(t_token *pipe);
t_token			*add_back_redirect(t_command *cmd, t_token *token);
t_token			*add_back_word(t_command *cmd, t_token *token);
char			*token_dup_word(const char *buf,
					const unsigned int len_buf, t_token *token);
int				fill_token(const char *buf, t_token *token,
					unsigned int *index_buf);
t_token			**parse_to_token(const char *buf, t_token **head);
void			transform_token(t_token *token);

//tree function

t_node			*create_node(t_token **head, int type_node,
					int *error, t_node *parent);
t_command		**create_command_array(t_token *token, int *error);
int				create_tree(t_token **head, t_node **node,
					int *error, t_node *parent);
int				is_logical_operator(const int type);
int				get_type_node(t_token *operator);

//free function

void			free_t_command(t_command **cmd);
void			ft_del_token(t_token *token);
void			free_token(t_token **head);
void			ft_del_node(t_node *node);
t_node			*go_to_root(t_node *node);
void			free_tree(t_node *root);

//here_doc function

char			*ft_strjoin_free_s1(char *s1, const char *s2,
					unsigned int *len_join);
char			*get_limiter(t_token *here_doc);
unsigned int	go_to_next_quotes(const char *str, char quotes);
void			get_stdin(t_token *here_doc, char *limiter,
					unsigned int len_lim);
void			do_here_doc(t_token *here_doc, t_token **head,
					int *previous_type);

unsigned int	skip_spaces(const char *buf);

#endif
