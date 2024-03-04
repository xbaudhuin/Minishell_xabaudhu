/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:35:31 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/04 12:31:31 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_type_node(t_token *operator)
{
	if (operator->type == AND)
		return (NODE_AND);
	if (operator->type == OR)
		return (NODE_OR);
	return (NODE_LEAF);
}

int	is_logical_operator(const int type)
{
	if (type == AND)
		return (TRUE);
	if (type == OR)
		return (TRUE);
	return (FALSE);
}

t_node	*go_to_root(t_node *node)
{
	if (node == NULL)
		return (NULL);
	while (node->parent_node != NULL)
	{
		node = node->parent_node;
	}
	return (node);
}
