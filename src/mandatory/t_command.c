/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:36:50 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/23 18:54:34 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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

static t_token	*add_back_redirect(t_command *cmd, t_token *token)
{
	t_token	*tmp_next;

	tmp_next = token->next;
	token->next = NULL;
	token->previous = NULL;
	if (tmp_next != NULL)
		tmp_next->previous = NULL;
	ft_token_add_back(&cmd->redirect_token, token);
	return (tmp_next);
}

static t_token	*add_back_word(t_command *cmd, t_token *token)
{
	t_token	*tmp_next;

	tmp_next = token->next;
	token->next = NULL;
	token->previous = NULL;
	if (tmp_next != NULL)
		tmp_next->previous = NULL;
	ft_token_add_back(&cmd->token, token);
	return (tmp_next);
}

static t_token	*remove_pipe(t_token *pipe)
{
	t_token	*next_token;

	next_token = pipe->next;
	if (next_token != NULL)
		next_token->previous = NULL;
	ft_del_token(pipe);
	return (next_token);
}

t_command	**init_command_array(const int nb_cmd)
{
	t_command		**cmd;
	int	i;

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
		cmd[i]->argv = NULL;
		cmd[i]->redirect_token = NULL;
		i++;
	}
	return (cmd);
}

t_command	**create_command_array(t_token *token, int *error)
{
	t_command		**cmd;
	unsigned int	nb_cmd;
	unsigned int	i;
	t_token			*tmp;

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
	i = 0;
	tmp = token;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
		{
			tmp = remove_pipe(tmp);
			i++;
		}
		else if (is_redirect_token(tmp->type) == TRUE)
		{
			tmp = add_back_redirect(cmd[i], tmp);
		}
		else if (tmp->type == WORD)
		{
			tmp = add_back_word(cmd[i], tmp);
		}
	}
	cmd[nb_cmd] = NULL;
	return (cmd);
}
