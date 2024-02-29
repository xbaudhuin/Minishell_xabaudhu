/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:17:31 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/29 17:33:01 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "minishell.h"
#include "parsing.h"

int	is_dollar_expandable(const char *word)
{
	unsigned int	i;

	i = 0;
	if (word == NULL)
		return (FALSE);
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
		if (word[i] == '$')
			return ();
		else
			i++;
	}
	return (FALSE);
}

unsigned int

unsigned int	get_len_env(char *word, const t_env env)
{
	char			save;
	char			*dollar;
	unsigned int	i;

	i = 0;
	while (is_dollar_char(word[i]) == TRUE)
		i++;
	save = word[i];
	word[i] = '\0';
	dollar = ft_getenv(word, env);
	if (dollar == NULL)
		return (0);
	return (ft_strlen(dollar));
}

unsigned int	get_len_dollar(const char *word, const t_env env)
{
	unsigned int	i;
	unsigned int	len_till_dollar;
	char			*dollar;
	unsigned int	len_total;

	i = 0;
	len_total = 0;
	len_till_dollar = 0;
	while (word[i] != '\0')
	{
		len_till_dollar = 
		i += len_till_dollar;
		len_total += len_till_dollar;
		if (word[i] == '\0')
			break ;
		i++;
		len_total += get_len_env((char *)&word[i], env);
		i += 
	}
}

char	do_dollar_expansion(char *word, const t_env env)
{
	unsigned int	i;
	unsigned int	len;
	char			*dollar;

	i = 0;
	len = get_len_dollar(word, env);
}

int	is_dollar_expandable(const char *word)
{
	unsigned int	i;

	i = 0;
	if (word == NULL)
		return (FALSE);
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
		if (word[i] == '$')
			return (TRUE);
		else
			i++;
	}
	return (FALSE);
}

int	expand_dollar_list(t_token *head, const t_env env)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (is_dollar_expandable(tmp->word) == TRUE)
		{
			if (do_dollar_expansion(tmp->word) == NULL)
				free_token(&head);
		}
	}
}

int	expand_dollar(t_command **cmd, const t_env env)
{
	unsigned int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->token)
		{
			if (expand_dollar_list(cmd[i]->token) == FAILURE)
				return (FAILURE);
		}
		if (cmd[i]->redirect_token)
		{
			if (expand_dollar_list(cmd[i]->redirect_token) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
