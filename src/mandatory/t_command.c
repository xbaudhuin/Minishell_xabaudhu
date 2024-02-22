/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:36:50 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/22 20:26:32 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

void	free_t_command(t_command **cmd)
{
	unsigned int	i;

	i = 0;
	if (cmd == NULL)
		return ;
	if (*cmd == NULL)
	{
		free(cmd);
		return ;
	}
	while (cmd[i])
	{
		free_token(&cmd[i]->redirect_token);
		free_token(&cmd[i]->token);
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

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

/*static void	swap_word(t_token **redirect, t_token **word)
{
	free((*redirect)->word);
	(*redirect)->word = (*word)->word;
	(*word)->word = NULL;
	(*redirect)->len_word = (*word)->len_word;
	(*redirect)->next = (*word)->next;
	(*word)->next->previous = (*redirect);
	free(*word);
}*//*
static void	cat_redirect(t_token *redirect, t_token *word)
{
	free(redirect->word);
	redirect->word = word->word;
	word->word = NULL;
	redirect->len_word = word->len_word;
	redirect->next = word->next;
	word->next->previous = redirect;
	free(word);
}

static void	add_back_redirect(t_command *cmd, t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (tmp->type != HERE_DOC)
		cat_redirect(tmp, tmp->next);
	if (tmp->previous == NULL)
	{
		(*token) = tmp->next;
		(*token)->previous = NULL;
	}
	else
	{
		tmp->previous->next = tmp->next;
		tmp->next->previous = tmp->previous;
	}
	tmp->next = NULL;
	tmp->previous = NULL;
	ft_token_add_back(&cmd->redirect_token, tmp);
}*/
/*
static void	add_back_word(t_command *cmd, t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (tmp->previous == NULL)
	{
		(*token) = tmp->next;
	}
	else
	{
		tmp->previous->next = tmp->next;
		tmp->next->previous = tmp->previous;
	}
	tmp->next = NULL;
	tmp->previous = NULL;
	ft_token_add_back(&cmd->token, tmp);
}
*/

t_command	*init_command_array(const int nb_cmd)
{
	t_command	*cmd;

	cmd = ft_calloc(sizeof(t_command), nb_cmd + 1);
	if (cmd == NULL)
		return (NULL);
	return (cmd);
}

t_command	*create_command_array(t_token *token, int *error)
{
	t_command		*cmd;
	unsigned int	nb_cmd;
	unsigned int	i;
	t_token			*tmp;
	t_token			*next_tmp;

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
			tmp = tmp->next;
			i++;
		}
		else if (is_redirect_token(tmp->type) == TRUE)
		{
			next_tmp = tmp->next->next;
			if (tmp->previous != NULL)
				tmp->previous->next = next_tmp;
			if (next_tmp != NULL)
				next_tmp->previous = tmp->previous;
			tmp->previous = NULL;
			free(tmp->word);
			tmp->word = tmp->next->word;
			tmp->next->word = NULL;
			ft_del_token(tmp->next);
			if (cmd[i].redirect_token == NULL)
				cmd[i].redirect_token = tmp;
			else
				ft_token_add_back(&cmd[i].redirect_token, tmp);
			tmp = next_tmp;
		}
		else if (tmp->type == WORD)
		{
			next_tmp = tmp;
			while (next_tmp != NULL && is_word_token(next_tmp->type) == TRUE)
				next_tmp = next_tmp->next;
			if (next_tmp != NULL)
				next_tmp->previous = NULL;
			if (cmd[i].token == NULL)
				cmd[i].token = tmp;
			else
				ft_token_add_back(&cmd[i].token, tmp);
			tmp = next_tmp;
		}
	}
	cmd[nb_cmd] = NULL;
	return (cmd);
}
