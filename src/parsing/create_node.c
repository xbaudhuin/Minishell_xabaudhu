/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:45:34 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/29 13:52:54 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(t_token **head, int type_node, int *error, t_node *parent)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
	{
		*error = 1;
		return (NULL);
	}
	node->exit_status = -1;
	node->type = type_node;
	if (type_node == NODE_LEAF)
		node->cmd = create_command_array(*head, error);
	else
	{
		node->cmd = NULL;
		free_token(head);
	}
	node->left_node = NULL;
	node->right_node = NULL;
	node->parent_node = parent;
	return (node);
}
