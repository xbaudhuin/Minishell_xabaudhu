/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:45:34 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/22 17:42:16 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(t_token **head, int type_node, int *error)
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
	node->parent_node = NULL;
	return (node);
}

void	ft_del_node(t_node *node)
{
	if (node != NULL)
	{
		if (node->cmd != NULL)
			free_t_command(node->cmd);
		free(node);
	}
}

void	free_tree(t_node **root)
{
	if (root == NULL || *root == NULL)
		return ;
	free_t_command((*root)->cmd);
	if ((*root)->right_node != NULL)
		free_tree(&(*root)->right_node);
	if ((*root)->left_node != NULL)
		free_tree(&(*root)->left_node);
	free((*root));
}

void	print_tree(t_node **root, int id)
{
	t_node	*tmp;
	unsigned int	i;

	i = 0;
	if (root == NULL || *root == NULL)
		return ;
	tmp = *root;
	ft_printf(GRN "node %d:\n" RESET, id);
	while (tmp->cmd[i])
	{
		ft_printf(BLU "command %u\n" RESET, i);
		ft_printf(BLU "token:\n" RESET);
		print_token(&tmp->cmd[i]->token);
		print_token(&tmp->cmd[i]->redirect_token);
		i++;
	}
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
