/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:24:40 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/27 17:24:40 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_tree(t_node *root, t_env *env)
{
	int		exit_status_left;

	exit_status_left = SUCCESS;
	if (root->type == NODE_LEAF)
	{
		return (test_fork(root->cmd[0], env, &root));
	}
	else
	{
		exit_status_left = launch_tree(root->left_node, env);
	}
	if ((exit_status_left == SUCCESS && root->type == NODE_AND)
		|| (exit_status_left != SUCCESS && root->type == NODE_OR))
	{
		return (launch_tree(root->right_node, env));
	}
	else
	{
		return (exit_status_left);
	}
}
