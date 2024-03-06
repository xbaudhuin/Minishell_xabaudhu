/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:14:26 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/06 15:48:11 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	ft_len_unb(unsigned int nb)
{
	unsigned int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

static unsigned int	get_len_env(
	char *word, const t_env env, unsigned int len_word)
{
	char			save;
	char			*dollar;
	unsigned int	len_expand;

	save = word[len_word];
	word[len_word] = '\0';
	dollar = ft_getenv(word, env);
	word[len_word] = save;
	if (dollar == NULL)
		return (0);
	len_expand = ft_strlen(dollar);
	return (len_expand);
}

static unsigned int	get_len_word_without_dollar(const char *word)
{
	unsigned int	i;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '\'')
		{
			i++;
			while (word[i] != '\0' && word[i] != '\'')
				i++;
			if (word[i] == '\'')
				i++;
		}
		else if (word[i] == '$')
			break ;
		else
			i++;
	}
	return (i);
}

int	len_if_dollar(
	const char *word, unsigned int *i, unsigned int *len_total, const t_env env)
{
	unsigned int	len_till_dollar;

	*i += 1;
	if (is_dollar_char(word[*i]) == FALSE && is_quotes(word[*i]) == FALSE)
	{
		*len_total += 1;
		if (word[*i] == '\0')
			return (FALSE);
	}
	if (word[*i] == '?')
	{
		*i += 1;
		*len_total += ft_len_unb(env.exit_status);
	}
	else
	{
		len_till_dollar = skip_dollar(&word[*i]);
		*len_total += get_len_env((char *)&word[*i], env, len_till_dollar);
		*i += len_till_dollar;
	}
	return (TRUE);
}

unsigned int	get_len_dollar(const char *word, const t_env env)
{
	unsigned int	i;
	unsigned int	len_till_dollar;
	unsigned int	len_total;

	i = 0;
	len_total = 0;
	len_till_dollar = 0;
	while (word[i] != '\0')
	{
		len_till_dollar = get_len_word_without_dollar(&word[i]);
		i += len_till_dollar;
		len_total += len_till_dollar;
		if (word[i] == '\0')
			break ;
		if (word[i] == '$')
		{
			if (len_if_dollar(word, &i, &len_total, env) == FALSE)
				break ;
		}
	}
	return (len_total);
}
