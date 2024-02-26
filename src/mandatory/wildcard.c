/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:27:46 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/26 18:24:50 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*compare_wildcard(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	if (ft_strlen(little) > len)
		return (NULL);
	while (big[i] && i < len)
	{
		j = 0;
		while (little[j] == big[i + j] && (i + j) < len)
		{
			j++;
			if (little[j] == '\0')
			{
				if (big[i + j] == '\0')
					return (NULL);
				return ((char *)&big[i]);
			}
		}
		i++;
	}
	return (NULL);
}

int	check_wildcard(char *str, const char *file_name, unsigned int *wildcard)
{
	if (compare_wildcard(file_name, str, *wildcard) != NULL)
	{
		if (ft_strlen(str) == *wildcard)
			return (free(str), TRUE);
	}
}

char	next_not_quote_char(const char *s)
{
	unsigned int	i;
	char			quotes;

	i = 0;
	if (is_quotes(s[i]))
		quotes = s[i];
	while (s[i] && s[i] == quotes)
		i++;
	return (s[i]);
}

unsigned int	dup_chr(const char *s, char *dup, char quotes)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != quotes)
	{
		dup[i] = s[i];
		i++;
	}
	return (i);
}

char	*trim_quotes(const char *s, unsigned int len)
{
	char			*trim_dup;
	unsigned int	i;
	unsigned int	j;
	unsigned int	len_quotes;

	trim_dup = ft_calloc(len, sizeof(*trim_dup) + 1);
	if (trim_dup == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0' && s[i] != '*')
	{
		if (is_quotes(s[i]))
		{
			len_quotes = dup_chr(&s[i + 1], &trim_dup[j], s[i]);
			i += len_quotes + 2;
			j += len_quotes;
		}
		trim_dup[j] = s[i];
		i++;
		j++;
	}
	trim_dup[j] = '\0';
	return (trim_dup);
}


int	is_wildcard_expendable(const char *word)
{
	unsigned int	i;
	char			quotes;

	i = 0;
	quotes = '\0';
	while (word[i])
	{
		if (is_quotes(word[i]))
		{
			quotes = word[i];
			while (word[i] && word[i] != quotes)
				i++;
		}
		if (word[i] == '*')
			return (TRUE);
	}
	return (FALSE);
}

int	get_nb_wildcard(const char *word, char c)
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
		{
			i += go_to_next_quotes(&word[i + 1], word[i]) + 1;
		}
		if (word[i] == c)
		{
			nb_wildcard++;
			while (word[i] == c)
				i++;
		}
		else
			i++;
	}
	return (nb_wildcard);
}

unsigned int	len_till_next_wildcard(const char *word)
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
		}
		if (word[i] == '*')
			break ;
		i++;
	}
	return (i);
}

char	**ft_split_wildcard(const char *word, unsigned int nb_wildcard)
{
	char			**split;
	unsigned int	i;
	unsigned int	len_to_wildcard;

	split = ft_calloc(nb_wildcard, sizeof(*split));
	if (split == NULL)
		return (NULL);
	while (word[i] != '\0')
	{
		len_to_wildcard = len_till_next_wildcard(&word[i]);
		split[k] = trim_quotes(&word[i], len_to_wildcard);
	}
}

char	*wildcard_expansion(const char *word, const char *file_name)
{
	unsigned int	nb_wildcard;
	char			**split_wildcard;

	nb_wildcard = get_nb_wildcard(word, '*');
	if (nb_wildcard == 0)
		return ((char *)word);
	split_wildcard = ft_split_wildcard(word, nb_wildcard);
}
