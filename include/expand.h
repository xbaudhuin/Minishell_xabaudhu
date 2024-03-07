/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:26:26 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/06 18:23:46 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <dirent.h>
# define HIDDEN_ON 0
# define HIDDEN_OFF 1

int				expand_token(t_command **cmd, const t_env env);
int				re_tokenize(t_token *token);
void			trim_quotes_all(t_command **cmd);
//wildcard function

DIR				*get_open_dir(void);
int				is_hidden_file(const char *word);
void			free_wildcard(char **split, unsigned int k);
char			**ft_split_wildcard(const char *word, unsigned int nb_wildcard);
int				compare_wildcard(char **split, unsigned int size_split, char *file);
char			*ft_strjoin_wildcard(char *s1, const char *s2);
char			*trim_quotes_wildcard(const char *s, unsigned int len);
int				expand_wildcard(t_command **cmd);
char			*do_expand_wildcard(char *word);
int				get_nb_wildcard(const char *word, char c);

//dollar function
unsigned int	skip_dollar(const char *word);
int				expand_dollar(t_command **cmd, const t_env env);
unsigned int	get_len_dollar(const char *word, const t_env env);
char			*do_dollar_expansion(char *word, const t_env env);

#endif
