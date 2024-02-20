/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:45:34 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/20 12:58:58 by xabaudhu         ###   ########.fr       */
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

void	free_tree(t_command_node **root)
{
	if (root == NULL || *root == NULL)
		return ;
	free_token(&(*root)->token);
	if ((*root)->right_node != NULL)
		free_tree(&(*root)->right_node);
	if ((*root)->left_node != NULL)
		free_tree(&(*root)->left_node);
	free((*root));
}

t_command_node *add_node(t_command_node **root, t_token *token, t_command_node *node)
{
	if (token->type == AND)
	{
		(*root)->left_node = node;
	}
	if (token->type == OR)
	{
		(*root)->right_node = node;
	}
	return (node);
}

void	print_tree(t_command_node **root, int id)
{
	t_command_node	*tmp;

	if (root == NULL || *root == NULL)
		return ;
	tmp = *root;
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
