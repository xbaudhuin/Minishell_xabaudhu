/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:17:31 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/04 17:09:00 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parsing.h"

unsigned int	get_len_word_without_dollar(const char *word)
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

unsigned int	skip_dollar(const char *word)
{
	unsigned int	i;

	i = 0;
	while (is_dollar_char(word[i])== TRUE)
		i++;
	return (i);
}

unsigned int	get_len_env(char *word, const t_env env, unsigned int len_word)
{
	char			save;
	char			*dollar;
	unsigned int	len_expand;

	save = word[len_word];
	word[len_word] = '\0';
	dollar = ft_getenv(word, env);
	if (dollar == NULL)
		return (0);
	len_expand = ft_strlen(dollar);
	word[len_word] = save;
	return (len_expand);
}

unsigned int	copy_from_env(char *word, char *dollar, const t_env env)
{
	unsigned int	len_word;
	unsigned int	len_name;
	char			save;
	char			*name;

	len_word = skip_dollar(word);
	save = word[len_word];
	word[len_word] = '\0';
	name = ft_getenv(word, env);
	len_name = ft_strlen(name);
	ft_memmove(dollar, name, len_name);
	return (len_word);
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
			i++;
		len_till_dollar = skip_dollar(&word[i]);
		len_total += get_len_env((char *)&word[i], env, len_till_dollar);
		i += len_till_dollar;
	}
	return (len_total);
}

unsigned int	copy_till_dollar(const char *source,char *dest, char c)
{
	unsigned int	i;
	int				flag_quotes;

	i = 0;
	flag_quotes= FALSE;
	while (source[i] != '\0')
	{
		if (source[i] == c && flag_quotes == FALSE)
			break ;
		if (source[i] == '\'')
		{
			if (flag_quotes == FALSE)
				flag_quotes = TRUE;
			else
				flag_quotes = FALSE;
		}
		dest[i] = source[i];
		i++;
	}
	return (i);
}

char	*do_dollar_expansion(char *word, const t_env env)
{
	unsigned int	i;
	unsigned int	len_dollar;
	char			*dollar;

	i = 0;
	len_dollar = get_len_dollar(word, env);
	dollar = ft_calloc(len_dollar + 1, sizeof(*dollar));
	if (dollar == NULL)
		return (FALSE);
	while (word[i] != '\0')
	{
		i += copy_till_dollar(&word[i], dollar, '$');
		if (word[i] == '\0')
			break ;
		if (word[i] == '$')
			i++;
		i += copy_from_env(&word[i], dollar, env);
	}
	free(word);
	dollar[len_dollar] = '\0';
	return (dollar);
}

int	is_dollar_expandable(const char *word)
{
	unsigned int	i;
	int				flag_quotes;

	i = 0;
	flag_quotes = FALSE;
	if (word == NULL)
		return (FALSE);
	while (word[i] != '\0')
	{
		if (word[i] == '\'')
		{
			if (flag_quotes == FALSE)
				flag_quotes = TRUE;
			else
				flag_quotes = TRUE;
		}
		if (word[i] == '$' && flag_quotes == FALSE)
			return (TRUE);
		else
			i++;
	}
	return (FALSE);
}

int	expand_dollar_list(t_token **head, const t_env env)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (is_dollar_expandable(tmp->word) == TRUE)
		{
			tmp->word = do_dollar_expansion(tmp->word, env);
			if (tmp->word == NULL)
			{
				free_token(head);
				return (FAILURE);
			}
			if (re_tokenize(tmp) == FAILURE)
			{
				free_token(head);
				return (FAILURE);
			}
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	expand_dollar(t_command **cmd, const t_env env)
{
	unsigned int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->token)
		{
			if (expand_dollar_list(&cmd[i]->token, env) == FAILURE)
				return (FAILURE);
		}
		if (cmd[i]->redirect_token)
		{
			if (expand_dollar_list(&cmd[i]->redirect_token, env) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
