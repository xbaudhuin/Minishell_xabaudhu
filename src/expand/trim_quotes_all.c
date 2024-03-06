/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:17:31 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/04 18:22:50 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parsing.h"

int	check_if_pass_quotes(char c, char *quotes)
{
	if (is_quotes(c))
	{
		if (*quotes == '\0')
		{
			*quotes = c;
			return (TRUE);
		}
		if (*quotes == c)
		{
			*quotes = '\0';
			return (TRUE);
		}
	}
	return (FALSE);
}

void	trim_quotes_word(char *word)
{
	unsigned int	i;
	unsigned int	j;
	char			quotes;

	i = 0;
	j = i;
	quotes = '\0';
	if (word == NULL)
		return ;
	while (word[i])
	{
		if (check_if_pass_quotes(word[i], &quotes) == TRUE)
			i++;
		else
		{
			word[j] = word[i];
			i++;
			j++;
		}
	}
	word[j] = '\0';
}

void	trim_quotes_list(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		if (tmp->word != NULL)
			trim_quotes_word(tmp->word);
		tmp = tmp->next;
	}
}

void	trim_quotes_all(t_command **cmd)
{
	unsigned int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (cmd[i]->token != NULL)
			trim_quotes_list(cmd[i]->token);
		if (cmd[i]->redirect_token != NULL)
			trim_quotes_list(cmd[i]->redirect_token);
		i++;
	}
}
