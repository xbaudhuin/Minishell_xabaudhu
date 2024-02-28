/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:26:26 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/28 20:44:28 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <dirent.h>

# define HIDDEN_ON 0
# define HIDDEN_OFF 1

//wildcard function

DIR		*get_open_dir(void);
int		is_hidden_file(const char *word);
void	free_wildcard(char **split, unsigned int k);
char	**ft_split_wildcard(const char *word, unsigned int nb_wildcard);
int		compare_wildcard(char **split, unsigned int size_split, char *file);
char	*ft_strjoin_wildcard(char *s1, const char *s2);
char	*trim_quotes_wildcard(const char *s, unsigned int len);

#endif
