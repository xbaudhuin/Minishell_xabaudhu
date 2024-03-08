/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nb_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:43:29 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/08 17:48:59 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	next_quotes_wildcard(
	const char *word, char quotes, int *flag, unsigned int *wildcard)
{
	unsigned int	i;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == quotes)
		{
			i++;
			break ;
		}
		if (*flag == 1)
		{
			*flag = 0;
			*wildcard += 1;
		}
		i++;
	}
	return (i);
}

static unsigned int	get_nb_equal_wildcard(
	const char *word, unsigned int *nb_wildcard, int *flag, char c)
{
	unsigned int	i;

	i = 0;
	*nb_wildcard += 1;
	*flag = 1;
	while (word[i] == c)
		i++;
	return (i);
}

static unsigned int	get_nb_not_wildcard(int *flag, unsigned int *nb_wildcard)
{
	if (*flag == 1)
	{
		*flag = 0;
		*nb_wildcard += 1;
	}
	return (1);
}

int	get_nb_wildcard(const char *word, char c)
{
	unsigned int	i;
	unsigned int	nb_wildcard;
	int				flag;

	i = 0;
	nb_wildcard = 0;
	flag = 1;
	while (word[i] != '\0')
	{
		if (is_quotes(word[i]))
			i += next_quotes_wildcard(&word[i + 1],
					word[i], &flag, &nb_wildcard) + 1;
		else if (word[i] == c)
		{
			i += get_nb_equal_wildcard(&word[i], &nb_wildcard, &flag, c);
		}
		else
			i += get_nb_not_wildcard(&flag, &nb_wildcard);
	}
	return (nb_wildcard);
}
