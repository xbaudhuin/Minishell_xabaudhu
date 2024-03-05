/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:34:15 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/05 14:54:44 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <errno.h>

static int	get_nb_wildcard(const char *word, char c)
{
	unsigned int	i;
	unsigned int	nb_wildcard;

	i = 0;
	nb_wildcard = 0;
	while (word[i] != '\0')
	{
		if (is_quotes(word[i]))
			i += go_to_next_quotes(&word[i + 1], word[i]) + 1;
		else if (word[i] == c)
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

int	is_wildcard_expandable(const char *word)
{
	if (get_nb_wildcard(word, '*') >= 1)
		return (TRUE);
	return (FALSE);
}

int	expand_wildcard_list(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (is_wildcard_expandable(tmp->word) == TRUE)
		{
			tmp->word = do_expand_wildcard(tmp->word);
			if (tmp->word == NULL)
			{
				free_token(head);
				return (FAILURE);
			}
			if (re_tokenize(tmp) == FAILURE)
			{
				free_token(head);
				return (FAILURE);
			}
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	expand_wildcard(t_command **cmd)
{
	unsigned int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->token)
		{
			if (expand_wildcard_list(&cmd[i]->token) == FAILURE)
				return (FAILURE);
		}
		if (cmd[i]->redirect_token)
		{
			if (expand_wildcard_list(&cmd[i]->redirect_token) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
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
