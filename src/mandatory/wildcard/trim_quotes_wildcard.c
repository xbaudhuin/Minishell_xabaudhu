/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:07 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/28 17:38:27 by xabaudhu         ###   ########.fr       */
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

char	*trim_quotes_wildcard(const char *s, unsigned int len)
{
	char			*trim_dup;

	trim_dup = ft_calloc(len, sizeof(*trim_dup) + 1);
	if (trim_dup == NULL)
		return (NULL);
	copy_trim_quotes_wildcard(s, trim_dup);
	return (trim_dup);
}
