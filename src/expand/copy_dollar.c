/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:21:29 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/11 11:51:18 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	handle_flag_quotes(const char c, char *flag_quotes)
{
	if (*flag_quotes == FALSE)
		*flag_quotes = c;
	else if (*flag_quotes == c)
		*flag_quotes = FALSE;
}

unsigned int	handle_dollar_noquotes(
	char *word, char *dollar, unsigned int *i_dollar, const t_env env)
{
	unsigned int	i;

	i = 1;
	if (word[i] == '?')
	{
		i++;
		add_exit_status(&dollar[*i_dollar], i_dollar, env);
	}
	else if (is_dollar_quotes(word[i], FALSE) == FALSE)
	{
		dollar[*i_dollar] = '$';
		*i_dollar += 1;
		if (word[i] == '\0')
			return (i);
	}
	else
		i += copy_from_env(&word[i], &dollar[*i_dollar], env, i_dollar);
	return (i);
}

unsigned int	handle_dollar_double_quotes(
	char *word, char *dollar, unsigned int *i_dollar, const t_env env)
{
	unsigned int	i;

	i = 1;
	if (word[i] == '?')
	{
		i++;
		add_exit_status(&dollar[*i_dollar], i_dollar, env);
	}
	else if (is_dollar_quotes(word[i], '"') == FALSE)
	{
		dollar[*i_dollar] = '$';
		*i_dollar += 1;
		if (word[i] == '\0')
			return (i);
	}
	else
		i += copy_from_env(&word[i], &dollar[*i_dollar], env, i_dollar);
	return (i);
}

void	copy_dollar(
	char *word, char *dollar, unsigned int *i_dollar, const t_env env)
{
	unsigned int	i;
	char			flag_quotes;

	i = 0;
	flag_quotes = FALSE;
	while (word[i] != '\0')
	{
		if (is_quotes(word[i]))
			handle_flag_quotes(word[i], &flag_quotes);
		if (word[i] == '$' && flag_quotes != '\'')
		{
			if (flag_quotes == FALSE)
				i += handle_dollar_noquotes(&word[i], dollar, i_dollar, env);
			else
				i += handle_dollar_double_quotes(&word[i], dollar, i_dollar, env);
		}
		else
		{
			dollar[*i_dollar] = word[i];
			*i_dollar += 1;
			i++;
		}
	}
}

char	*do_dollar_expansion(char *word, const t_env env)
{
	unsigned int	index_dollar;
	char			*dollar;

	index_dollar = 0;
	dollar = ft_calloc(get_len_dollar(word, env) + 1, sizeof(*dollar));
	if (dollar == NULL)
		return (FALSE);
	copy_dollar(word, dollar, &index_dollar, env);
	dollar[index_dollar] = '\0';
	free(word);
	return (dollar);
}
