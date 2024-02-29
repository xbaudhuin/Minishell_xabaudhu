/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:17:55 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/27 14:17:56 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_cmd_argv(const t_command *cmd)
{
	t_token	*tmp_token;
	char	**argv;
	int		nb_word;

	tmp_token = cmd->token;
	nb_word = 0;
	while (tmp_token != NULL)
	{
		++nb_word;
		tmp_token = tmp_token->next;
	}
	argv = ft_calloc(sizeof (*argv), nb_word + 1);
	if (argv == NULL)
		return (NULL);
	tmp_token = cmd->token;
	nb_word = 0;
	while (tmp_token != NULL)
	{
		argv[nb_word] = ft_strdup(tmp_token->word);
		if (argv[nb_word] == NULL)
			return (free_split(argv), NULL);
		++nb_word;
		tmp_token = tmp_token->next;
	}
	return (argv);
}
