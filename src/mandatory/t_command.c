/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:36:50 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/21 20:51:57 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

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
}*/
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
}

static void	add_back_word(t_command *cmd, t_token **token)
{
	t_token	*tmp;

	tmp = *token;
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
	ft_token_add_back(&cmd->token, tmp);
}

t_command	**create_command_array(t_token *token)
{
	t_command		**cmd;
	unsigned int	nb_cmd;
	unsigned int	i;
	t_token			*tmp;

	if (token == NULL)
		return (NULL);
	nb_cmd = get_nb_pipe(token) + 1;
	cmd = malloc(sizeof(t_command *) * (nb_cmd + 1));
	if (cmd == NULL)
	{
		perror(RED "minishell: fail create_command: "RESET);
		return (NULL);
	}
	i = 0;
	tmp = token;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
			i++;
		if (is_redirect_token(tmp->type) == TRUE)
		{
			add_back_redirect(cmd[i], &tmp);
		}
		if (tmp->type == WORD)
			add_back_word(cmd[i], &tmp);
		tmp = tmp->next;
	}
	cmd[nb_cmd + 1] = NULL;
	return (cmd);
}
