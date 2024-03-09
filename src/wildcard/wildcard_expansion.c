/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:21:53 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/09 12:54:55 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*compare_split_vs_file(char *word, char **split,
							unsigned int size_split, int mode)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*str;

	dir = get_open_dir();
	str = NULL;
	if (dir == NULL)
		return (word);
	errno = 0;
	while (1)
	{
		ent = readdir(dir);
		while (ent && ent->d_name[0] == '.' && mode == HIDDEN_OFF)
			ent = readdir(dir);
		if (ent == NULL)
			break ;
		if (compare_wildcard(split, size_split, ent->d_name) == TRUE)
		{
			str = ft_strjoin_wildcard(str, ent->d_name);
			if (str == NULL)
				break ;
		}
	}
	closedir(dir);
	return (str);
}

static char	*wildcard_expansion(char *word, unsigned int size_split, int mode)
{
	char			*str;
	char			**split_word;

	split_word = ft_split_wildcard(word, size_split);
	if (split_word == NULL)
		return (word);
	str = compare_split_vs_file(word, split_word, size_split, mode);
	free_wildcard(split_word, size_split);
	if (errno)
	{
		free(str);
		free(word);
		str = NULL;
		perror(RED"wildcard_expansion:"RESET);
		return (NULL);
	}
	if (str == NULL)
		return (word);
	free(word);
	return (str);
}

char	*do_expand_wildcard(char *word)
{
	unsigned int	nb_wildcard;
	char			*str;
	int				mode;

	str = NULL;
	if (word == NULL)
		return (NULL);
	nb_wildcard = get_nb_wildcard(word, '*');
	if (nb_wildcard == 0)
	{
		return ((char *)word);
	}
	mode = is_hidden_file(word);
	str = wildcard_expansion(word, nb_wildcard, mode);
	return (str);
}
