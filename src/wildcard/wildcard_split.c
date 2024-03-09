/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:53:22 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/09 15:16:16 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_wildcard(char **split, unsigned int k)
{
	unsigned int	i;

	i = 0;
	if (split == NULL)
		return ;
	while (i < k)
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}

static unsigned int	len_till_next_wildcard(const char *word)
{
	unsigned int	i;
	char			quotes;

	i = 0;
	while (word[i] != '\0')
	{
		if (is_quotes(word[i]))
		{
			quotes = word[i];
			i++;
			while (word[i] != '\0' && word[i] != quotes)
			{
				i++;
			}
			i++;
		}
		else if (word[i] == '*')
			break ;
		else
			i++;
	}
	return (i);
}

static unsigned int	skip_char(const char *word, char c)
{
	unsigned int	i;

	i = 0;
	while (word[i] == c)
		i++;
	return (i);
}

static int	fill_split_wildcard(
	char **split, const char *word, const unsigned int size_split)
{
	unsigned int	i;
	unsigned int	len_to_wildcard;
	unsigned int	k;

	k = 0;
	i = 0;
	while (word[i] != '\0' && k < size_split)
	{
		len_to_wildcard = len_till_next_wildcard(&word[i]);
		if (len_to_wildcard == 0)
		{
			split[k] = NULL;
			k++;
			i += skip_char(&word[i], '*');
		}
		else
		{
			if (trim_quotes_wildcard(
					&word[i], len_to_wildcard, split, &k) == FAILURE)
				return (free_wildcard(split, k), FAILURE);
			i += len_to_wildcard;
		}
	}
	return (SUCCESS);
}

char	**ft_split_wildcard(const char *word, unsigned int nb_wildcard)
{
	char			**split_wildcard;

	split_wildcard = NULL;
	split_wildcard = ft_calloc(nb_wildcard, sizeof(*split_wildcard));
	if (split_wildcard == NULL)
		return (NULL);
	if (fill_split_wildcard(split_wildcard, word, nb_wildcard) == FAILURE)
	{
		perror(RED"split_wildcard"RESET);
		return (NULL);
	}
	return (split_wildcard);
}
