/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 20:22:27 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/19 21:23:05 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_next_command(const int type)
{
	if (is_word_token(type) == TRUE)
		return (TRUE);
	if (is_redirect_token(type) == TRUE)
		return (TRUE);
	if (is_parenthesis_token(type) == TRUE)
		return (TRUE);
	if (type == PIPE)
		return (TRUE);
	if (is_operator_token(type) == TRUE)
		return (FALSE);
	return (FALSE);
}

t_command_node	*get_current_node(t_token **head)
{
	t_token			*tmp;
	t_command_node	*node;

	tmp = *head;
	while (tmp)
	{
		if (is_next_command(tmp->type) == FALSE)
			break ;
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	node = create_node();
	if (!node)
		return (NULL);
	node->token = (*head);
	(*head) = tmp->next;
	return (node);
}

t_command_node	**token_to_tree(t_token **head, t_command_node **root)
{
	int	flag;
	t_token	*tmp;
	t_command_node	*node;

	flag = 0;
	tmp = *head;
	while (tmp)
	{
		node = get_current_node(&tmp);
		if (node == NULL)
		{
			free_tree(root);
			free_token(head);
			return (NULL);
		}
		add_node(root, tmp, node);
	}
	return (root);
}
