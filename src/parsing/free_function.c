/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:54:15 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/06 15:11:36 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_command(t_command **cmd)
{
	unsigned int	i;

	i = 0;
	if (cmd == NULL)
		return ;
	if (*cmd == NULL)
	{
		free(cmd);
		return ;
	}
	while (cmd[i])
	{
		free_token(&cmd[i]->redirect_token);
		free_token(&cmd[i]->token);
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
	free(cmd);
}

void	ft_del_token(t_token *token)
{
	if (token != NULL)
	{
		if (token->word != NULL)
		{
			free(token->word);
			token->word = NULL;
		}
		free(token);
		token = NULL;
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

void	ft_del_node(t_node *node)
{
	if (node != NULL)
	{
		if (node->cmd != NULL)
			free_t_command(node->cmd);
		free(node);
	}
}

void	free_tree(t_node *root)
{
	if (root == NULL || root == NULL)
		return ;
	if (root->cmd != NULL)
		free_t_command(root->cmd);
	root->cmd = NULL;
	free_tree(root->right_node);
	root->right_node = NULL;
	free_tree(root->left_node);
	root->left_node = NULL;
	free(root);
	root = NULL;
}
