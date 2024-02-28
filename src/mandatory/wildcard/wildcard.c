/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:34:15 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/28 20:35:10 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <errno.h>

static int	get_nb_wildcard(const char *word, char c)
{
	unsigned int	i;
	unsigned int	nb_wildcard;
	char			quotes;

	i = 0;
	nb_wildcard = 0;
	quotes = '\0';
	while (word[i] != '\0')
	{
		if (is_quotes(word[i]))
			i += go_to_next_quotes(&word[i + 1], word[i]) + 1;
		if (word[i] == c)
		{
			nb_wildcard++;
			while (word[i] == c)
				i++;
			if (word[i] != '\0')
				nb_wildcard++;
		}
		else
			i++;
	}
	if (nb_wildcard > 0 && word[0] != '*')
		nb_wildcard++;
	return (nb_wildcard);
}

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
	while (1)
	{
		ent = readdir(dir);
		while (ent->d_name[0] == '.' && mode == HIDDEN_OFF)
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
		perror(RED"wildcard_expansion:"RESET);
		return (free(str), NULL);
	}
	if (str == NULL)
		return (word);
	free(word);
	return (str);
}

char	*wildcard(char *word)
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
/*
#include <strings.h>

int main(int ac, char **av)
{
	(void)ac;
	char *str = NULL;
	str = strdup(av[1]);
	str = wildcard(str);
	if (str == NULL)
	{
		ft_printf(RED"str = NULL\n"RESET);
		return (0);
	}
	ft_printf("%s\n", str);
	free(str);
	return (0);
}*/