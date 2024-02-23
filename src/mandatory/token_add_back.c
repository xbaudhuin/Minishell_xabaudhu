/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:18:01 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/22 17:22:36 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"

char	*get_type(const int type)
{
	if (type == ERROR)
		return ("ERROR");
	if (type == PARENTHESIS_OPEN)
		return ("PARENTHESIS_OPEN");
	if (type == PARENTHESIS_CLOSE)
		return ("PARENTHESIS_CLOSE");
	if (type == WORD)
		return (RED"WORD"RESET);
	if (type == PIPE)
		return ("PIPE");
	if (type == AND)
		return ("AND");
	if (type == OR)
		return ("OR");
	if (type == REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == HERE_DOC)
		return ("HERE_DOC");
	if (type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (type == APPEND_OUT)
		return ("APPEND_OUT");
	return (NULL);
}

void	print_token(t_token **head)
{
	t_token			*tmp;
	unsigned int	i;

	i = 0;
	if (head == NULL || *head == NULL)
		return ;
	tmp = *head;
	i++;
	while (tmp)
	{
		ft_printf(GRN"token_%d:\n"RESET, i);
		ft_printf(BLU"token->len =%u\n", tmp->len_word);
		ft_printf("token->type=%s\n"RESET, get_type(tmp->type));
		ft_printf(BLU"token->depths=%d\n"RESET, tmp->depths);
		ft_printf("%s"RED"END""\n\n" RESET, tmp->word);
		tmp = tmp->next;
		i++;
	}
}

void	ft_del_token(t_token *token)
{
	if (token != NULL)
	{
		if (token->word != NULL)
			free(token->word);
		free(token);
	}
}

void	free_token(t_token **head)
{
	t_token	*tmp;

	if (head == NULL || *head == NULL)
		return ;
	tmp = *head;
	while (*head)
	{
		tmp = (*head)->next;
		ft_del_token(*head);
		*head = tmp;
	}
	head = NULL;
}

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->len_word = 0;
	token->word = NULL;
	token->next = NULL;
	token->depths = 0;
	token->type = 0;
	token->previous = NULL;
	return (token);
}

static t_token	*ft_token_last(t_token *token)
{
	if (token)
	{
		while (token->next)
			token = token->next;
		return (token);
	}
	return (NULL);
}

void	ft_token_add_back(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (head != NULL)
	{
		if (*head != NULL)
		{
			tmp = ft_token_last(*head);
			tmp->next = new;
			new->previous = tmp;
		}
		else
			*head = new;
	}
}
