/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:27:46 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/25 19:06:03 by xabaudhu         ###   ########.fr       */
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
				return ((char *)&big[i + j]);
			}
		}
		i++;
	}
	return (NULL);
}
unsigned int	go_to_next_wildcard(const char *str, char quotes, unsigned int i)
{
	while (str[i])
	{
		if (str[i] == quotes)
			break ;
		if (quotes == '\0' && is_quotes(str[i]))
			i += go_to_next_wildcard(&str[i + 1], str[i], i + 1);
		if (quotes == '\0' && str[i] == '*')
			break ;
		i++;
	}
	return (i);
}
int	check_wildcard(char *str, const char *file_name, unsigned int *wildcard)
{
	char	*to_cmp;

	to_cmp = compare_wildcard(file_name, str, *wildcard);
	if (to_cmp != NULL)
	{
		if (ft_strlen(str) == *wildcard)
			return (free(str), TRUE);
		compare_wildcard(to_cmp, const char *little, size_t len)
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

char	*trim_quotes(const char *s, unsigned int len, unsigned int *wildcard)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;
	char			quotes;


	str = ft_calloc(len, sizeof(*str) + 2);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	quotes = '\0';
	while (s[i] && s[i] != '*')
	{
		if (is_quotes(s[i]))
		{
			quotes = s[i];
			i++;
			while (s[i] && s[i] != quotes)
			{
				str[j] = s[i];
				i++;
				j++;
			}
			i++;
		}
		str[j] = s[i];
		j++;
		i++;
	}
	str[j] = s[i];
	if (s[i] != '\0')
	{
		j++;
		str[j] = next_not_quote_char(&s[j]);
	}
	*wildcard = j;
	str[j + 1] = '\0';
	return (str);
}

char	*next_wildcard(const char *word, const char *file_name)
{
	unsigned int	i;
	unsigned int	wildcard;
	unsigned int	len_till_wildcard;
	char			quotes;

	while (*word)
	{
		len_till_wildcard = go_to_next_wildcard(word, '\0', 0);
		if (word[len_till_wildcard] == '\0')
			break;
		check_wildcard(trim_quotes(word, len_till_wildcard, &wildcard), file_name, &wildcard);
	}
}

int	wildcard_expansion(char *word, const char *file_name)
{
	next_wildcard(&word[i], &file_name[j]);
}
