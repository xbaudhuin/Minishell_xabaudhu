/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes_wildcard.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:07 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/09 12:49:03 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	dup_chr(const char *s, char *dup, char quotes)
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

static void	copy_trim_quotes_wildcard(const char *source, char *dest)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	len_quotes;

	i = 0;
	j = 0;
	while (source[i] != '\0' && source[i] != '*')
	{
		if (is_quotes(source[i]))
		{
			len_quotes = dup_chr(&source[i + 1], &dest[j], source[i]);
			i += len_quotes + 2;
			j += len_quotes;
		}
		else
		{
			dest[j] = source[i];
			i++;
			j++;
		}
	}
	dest[j] = '\0';
}

int	trim_quotes_wildcard(
	const char *s, unsigned int len, char **split, unsigned int *k)
{
	split[*k] = ft_calloc(len, sizeof(char) + 1);
	if (split[*k] == NULL)
		return (FAILURE);
	copy_trim_quotes_wildcard(s, split[*k]);
	if (split[*k][0] == '\0')
	{
		free(split[*k]);
		split[*k] = NULL;
	}
	else
	{
		*k += 1;
	}
	return (SUCCESS);
}
