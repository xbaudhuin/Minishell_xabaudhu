/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:36:50 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/07 14:08:08 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static unsigned int	get_nb_pipe(const t_token *token)
{
	t_token			*tmp;
	unsigned int	nb_pipe;

	nb_pipe = 0;
	tmp = (t_token *)token;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
			nb_pipe++;
		tmp = tmp->next;
	}
	return (nb_pipe);
}

static t_command	**init_command_array(const int nb_cmd)
{
	t_command		**cmd;
	int				i;

	i = 0;
	cmd = ft_calloc(sizeof(t_command *), nb_cmd + 1);
	if (cmd == NULL)
		return (NULL);
	while (i < nb_cmd)
	{
		cmd[i] = malloc(sizeof(t_command));
		if (cmd[i] == NULL)
			return (free_t_command(cmd), NULL);
		cmd[i]->token = NULL;
		cmd[i]->redirect_token = NULL;
		i++;
	}
	return (cmd);
}

static void	fill_and_trim_command_array(
			t_command **cmd, t_token *token, unsigned int nb_cmd)
{
	unsigned int	i;

	i = 0;
	while (token != NULL)
	{
		if (token->type == PIPE)
		{
			token = remove_pipe(token);
			i++;
		}
		else if (is_redirect_token(token->type) == TRUE || is_here_doc_token(token->type) == TRUE)
		{
			token = add_back_redirect(cmd[i], token);
		}
		else if (token->type == WORD)
		{
			token = add_back_word(cmd[i], token);
		}
	}
	cmd[nb_cmd] = NULL;
}

t_command	**create_command_array(t_token *token, int *error)
{
	t_command		**cmd;
	unsigned int	nb_cmd;

	if (token == NULL)
		return (NULL);
	nb_cmd = get_nb_pipe(token) + 1;
	cmd = init_command_array(nb_cmd);
	if (cmd == NULL)
	{
		*error = 1;
		perror(RED "minishell: fail create_command: "RESET);
		return (NULL);
	}
	fill_and_trim_command_array(cmd, token, nb_cmd);
	return (cmd);
}
