/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:33:14 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/22 17:48:04 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_logical_operator(const int type)
{
	if (type == AND)
		return (TRUE);
	if (type == OR)
		return (TRUE);
	return (FALSE);
}

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

int	get_type_node(t_token *operator)
{
	if (operator->type == AND)
		return (NODE_AND);
	if (operator->type == OR)
		return (NODE_OR);
	return (NODE_LEAF);
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
	left_node_token = NULL;
	right_node_token = NULL;
	operator = get_next_prio_operator(head);
	if (operator == NULL)
	{
		*node = create_node(head, NODE_LEAF, error);
		if (error != 0)
			return (FAILURE);
		return (SUCCESS);
	}
	if (operator->previous != NULL)
	{
		left_node_token = operator->previous;
		left_node_token->next = NULL;
		operator->previous = NULL;
	}
	if (operator->next != NULL)
	{
		right_node_token = operator->next;
		right_node_token->previous = NULL;
		operator->next = NULL;
	}
	*node = create_node(&operator, get_type_node(operator), error);
	if (right_node_token != NULL)
	{
		create_tree(&left_node_token, &(*node)->left_node, error);
	}
	if (left_node_token != NULL)
	{
		create_tree(&right_node_token, &(*node)->right_node, error);
	}
	free_token(&operator);
	return (SUCCESS);
}
