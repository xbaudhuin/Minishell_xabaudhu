/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:45:34 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/19 20:20:31 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command_node	*create_node(void)
{
	t_command_node	*node;

	node = malloc(sizeof(t_command_node));
	if (node == NULL)
		return (NULL);
	node->left_node = NULL;
	node->right_node = NULL;
	node->parent_node = NULL;
	node->nb_command = 0;
	return (node);
}

void	ft_del_node(t_command_node *node)
{
	if (node != NULL)
	{
		if (node->token != NULL)
			free_token(&node->token);
		free(node);
	}
}

void	free_tree(t_command_node **head)
{
	if (head == NULL || *head == NULL)
		return ;
	free_token(&(*head)->token);
	if ((*head)->right_node != NULL)
		free_tree(&(*head)->right_node);
	if ((*head)->left_node != NULL)
		free_tree(&(*head)->left_node);
	free((*head));
}

void	print_tree(t_command_node **head, int id)
{
	t_command_node	*tmp;

	if (head == NULL || *head == NULL)
		return ;
	tmp = *head;
	ft_printf(GRN "node %d:\n" RESET, id);
	print_token(&tmp->token);
	if (tmp->left_node != NULL)
	{
		ft_printf(BLU "LEFT_NODE\n"RESET);
		print_tree(&tmp->left_node, id + 1);
	}
	if (tmp->right_node != NULL)
	{
		ft_printf(BLU "RIGHT_NODE\n"RESET);
		print_tree(&tmp->right_node, id +1);
	}
}
