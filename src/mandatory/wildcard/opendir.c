/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:04:58 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/28 17:27:41 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

DIR	*get_open_dir(void)
{
	DIR		*dir;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror(RED"wildcard_getcwd:"RESET);
		return (NULL);
	}
	dir = opendir(pwd);
	free(pwd);
	if (dir == NULL)
		return (NULL);
	return (dir);
}

static char	go_to_next_non_quoted_char(const char *word)
{
	unsigned int	i;
	char			quotes;

	i = 0;
	quotes = '\0';
	while (word[i])
	{
		if (is_quotes(word[i]) && quotes == '\0')
		{
			quotes = word[i];
			i++;
		}
		else if (word[i] == quotes)
		{
			quotes = '\0';
			i++;
		}
		else
			break ;
	}
	return (word[i]);
}

int	is_hidden_file(const char *word)
{
	char	first_char;

	first_char = go_to_next_non_quoted_char(word);
	if (first_char == '.')
		return (HIDDEN_ON);
	else
		return (HIDDEN_OFF);
}
