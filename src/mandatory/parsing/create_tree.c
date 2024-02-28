/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:33:14 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/28 18:36:19 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*get_next_prio_operator(t_token **head)
{
	t_token	*operator;
	t_token	*tmp;

	if (head == NULL)
		return (NULL);
	tmp = (*head)->next;
	operator = *head;
	while (tmp)
	{
		if (is_logical_operator(tmp->type) && tmp->depths <= operator->depths)
		{
			operator = tmp;
		}
		tmp = tmp->next;
	}
	if (is_logical_operator(operator->type) == FALSE)
		return (NULL);
	return (operator);
}

static void	break_list(t_token *operator, t_token **left_t, t_token **right_t)
{
	*left_t = NULL;
	*right_t = NULL;
	if (operator->previous != NULL)
	{
		*left_t = operator->previous;
		(*left_t)->next = NULL;
		operator->previous = NULL;
	}
	if (operator->next != NULL)
	{
		*right_t = operator->next;
		(*right_t)->previous = NULL;
		operator->next = NULL;
	}
}

int	create_tree(t_token **head, t_node **node, int *error)
{
	t_token	*left_node_token;
	t_token	*right_node_token;
	t_token	*operator;

	if (head == NULL || (*head) == NULL)
		return (SUCCESS);
	if (*error != 0)
		return (FAILURE);
	operator = get_next_prio_operator(head);
	if (operator == NULL)
	{
		*node = create_node(head, NODE_LEAF, error);
		if (*error != 0)
			return (FAILURE);
		return (SUCCESS);
	}
	break_list(operator, &left_node_token, &right_node_token);
	*node = create_node(&operator, get_type_node(operator), error);
	create_tree(head, &(*node)->left_node, error);
	create_tree(&right_node_token, &(*node)->right_node, error);
	free_token(&operator);
	return (SUCCESS);
}
