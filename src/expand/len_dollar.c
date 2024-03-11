/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:14:26 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/11 15:48:21 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parsing.h"

static unsigned int	len_skip_quotes(const char *word, char *flag_quotes)
{
	unsigned int	i;

	i = 0;
	if (*flag_quotes == FALSE)
		*flag_quotes = word[i];
	else if (*flag_quotes == word[i])
	{
		*flag_quotes = FALSE;
		return (i);
	}
	i++;
	while (word[i] != '\0' && is_dollar_quotes(word[i], *flag_quotes) == TRUE)
		i++;
	if (word[i] == *flag_quotes)
	{
		i++;
		*flag_quotes = FALSE;
	}
	return (i);
}

static unsigned int	get_len_word_without_dollar(
	const char *word, char *flag_quotes)
{
	unsigned int	i;

	i = 0;
	while (word[i] != '\0')
	{
		if (is_quotes(word[i]) && (*flag_quotes == FALSE))
		{
			i += len_skip_quotes(&word[i], flag_quotes);
		}
		else if (word[i] == '$')
			break ;
		else
			i++;
	}
	return (i);
}

static unsigned int	check_digit(unsigned int *len_total)
{
	*len_total += 2;
	return (1);
}

unsigned int	len_if_dollar(const char *word,
					unsigned int *len_total, const t_env env, char *flag_quotes)
{
	unsigned int	len_till_dollar;
	unsigned int	i;

	i = 1;
	if (is_dollar_quotes(word[i], *flag_quotes) == FALSE)
	{
		*len_total += 1;
		if (word[i] == '\0')
			return (i);
	}
	if (word[i] == '?')
	{
		i += 1;
		*len_total += ft_len_unb(env.exit_status);
	}
	else if (ft_isdigit(word[i]) == TRUE)
		i += check_digit(len_total);
	else
	{
		len_till_dollar = skip_dollar(&word[i]);
		*len_total += get_len_env((char *)&word[i], env, len_till_dollar);
		i += len_till_dollar;
	}
	return (i);
}

unsigned int	get_len_dollar(const char *word, const t_env env)
{
	unsigned int	i;
	unsigned int	len_till_dollar;
	unsigned int	len_total;
	char			flag_quotes;

	i = 0;
	len_total = 0;
	len_till_dollar = 0;
	flag_quotes = FALSE;
	while (word[i] != '\0')
	{
		len_till_dollar = get_len_word_without_dollar(&word[i], &flag_quotes);
		i += len_till_dollar;
		len_total += len_till_dollar;
		if (word[i] == '\0')
			break ;
		if (word[i] == '$' && flag_quotes != '\'')
		{
			i += len_if_dollar(&word[i], &len_total, env, &flag_quotes);
			if (word[i] == '\0')
				break ;
		}
	}
	return (len_total);
}
