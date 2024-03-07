/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:21:29 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/07 12:03:24 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	add_exit_status(char *dollar, unsigned int *index, const t_env env)
{
	char			name[4];
	unsigned char	nb;
	unsigned int	i;

	ft_bzero(name, 4);
	nb = env.exit_status;
	i = 0;
	if (env.exit_status >= 100)
	{
		name[i] = env.exit_status / 100 + 48;
		nb = env.exit_status % 100;
		i++;
	}
	if (nb >= 10)
	{
		name[i] = nb / 10 + 48;
		nb = nb % 10;
		i++;
	}
	name[i] = nb + 48;
	i++;
	ft_memmove(dollar, name, i);
	*index += i;
}

unsigned int	copy_from_env(
	char *word, char *dollar, const t_env env, unsigned int *index_dollar)
{
	unsigned int	len_word;
	unsigned int	len_name;
	char			save;
	char			*name;

	len_word = skip_dollar(word);
	save = word[len_word];
	word[len_word] = '\0';
	name = ft_getenv(word, env);
	word[len_word] = save;
	len_name = ft_strlen(name);
	ft_memmove(dollar, name, len_name);
	*index_dollar += len_name;
	return (len_word);
}

unsigned int	copy_till_dollar(
	const char *source, char *dest, char c, unsigned int *index_dollar)
{
	unsigned int	i;
	int				flag_quotes;

	i = 0;
	flag_quotes = FALSE;
	while (source[i] != '\0')
	{
		if (source[i] == c && flag_quotes != '\'')
			break ;
		if (is_quotes(source[i]))
		{
			if (flag_quotes == FALSE)
				flag_quotes = source[i];
			else if (flag_quotes == source[i])
				flag_quotes = FALSE;
		}
		dest[i] = source[i];
		i++;
	}
	*index_dollar += i;
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
		{
			if (flag_quotes == FALSE)
				flag_quotes = word[i];
			else if (flag_quotes == word[i])
				flag_quotes = FALSE;
		}
		if (word[i] == '$' && flag_quotes != '\'')
		{
			i++;
			if (word[i] == '?')
			{
				i++;
				add_exit_status(&dollar[*i_dollar], i_dollar, env);
			}
			else if (is_dollar_quotes(word[i], flag_quotes) == FALSE)
			{
				dollar[*i_dollar] = '$';
				*i_dollar += 1;
				if (word[i] == '\0')
					return ;
			}
			else
				i += copy_from_env(&word[i], &dollar[*i_dollar], env, i_dollar);

		}
		else
		{
			dollar[*i_dollar] = word[i];
			*i_dollar += 1;
			i++;
		}

	/*	i += copy_till_dollar(&word[i], &dollar[*i_dollar], '$', i_dollar);
		if (word[i] == '$')
		{
			i++;
			if (word[i] == '?')
			{
				i++;
				add_exit_status(&dollar[*i_dollar], i_dollar, env);
			}
			else if (is_dollar_quotes(word[i]) == FALSE)
			{
				dollar[*i_dollar] = '$';
				*i_dollar += 1;
				if (word[i] == '\0')
					return ;
			}
			else
				i += copy_from_env(&word[i], &dollar[*i_dollar], env, i_dollar);
		}*/
	}
}

char	*do_dollar_expansion(char *word, const t_env env)
{
	unsigned int	i;
	unsigned int	index_dollar;
	char			*dollar;

	i = 0;
	index_dollar = 0;
	dollar = ft_calloc(get_len_dollar(word, env) + 1, sizeof(*dollar));
	if (dollar == NULL)
		return (FALSE);
	copy_dollar(word, dollar, &index_dollar, env);
	dollar[index_dollar] = '\0';
	free(word);
	return (dollar);
}
