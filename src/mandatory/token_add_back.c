/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:18:01 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/15 18:13:31 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"

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
		ft_printf("token->type=%d\n"RESET, tmp->type);
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
	token->type = 0;
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
	if (head)
	{
		if (*head)
			ft_token_last(*head)->next = new;
		else
			*head = new;
	}
}
