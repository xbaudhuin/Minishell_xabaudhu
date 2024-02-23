/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:42:19 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/23 18:50:29 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_type(const int type)
{
	if (type == ERROR)
		return ("ERROR");
	if (type == PARENTHESIS_OPEN)
		return ("PARENTHESIS_OPEN");
	if (type == PARENTHESIS_CLOSE)
		return ("PARENTHESIS_CLOSE");
	if (type == WORD)
		return (RED"WORD"RESET);
	if (type == PIPE)
		return ("PIPE");
	if (type == AND)
		return ("AND");
	if (type == OR)
		return ("OR");
	if (type == REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == HERE_DOC)
		return ("HERE_DOC");
	if (type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (type == APPEND_OUT)
		return ("APPEND_OUT");
	return (NULL);
}

void	print_token(t_token **head)
{
	t_token			*tmp;
	unsigned int	i;

	i = 0;
	if (head == NULL || *head == NULL)
		return ;
	tmp = *head;
	i++;
	while (tmp)
	{
		ft_printf(GRN"token_%d:\n"RESET, i);
		ft_printf(BLU"token->len =%u\n", tmp->len_word);
		ft_printf("token->type=%s\n"RESET, get_type(tmp->type));
		ft_printf(BLU"token->depths=%d\n"RESET, tmp->depths);
		ft_printf("%s"RED"END""\n\n" RESET, tmp->word);
		tmp = tmp->next;
		i++;
	}
}

static char	*get_node_type(int type)
{
	if (type == NODE_ERROR)
		return ("ERROR");
	if (type == NODE_ROOT)
		return ("NODE_ROOT");
	if (type == NODE_LEAF)
		return ("NODE_LEAF");
	if (type == NODE_AND)
		return ("NODE_AND");
	if (type == NODE_OR)
		return ("NODE_OR");
	return ("Wrong node type");
}

void	print_tree(t_node **root, int id)
{
	t_node			*tmp;
	unsigned int	i;

	i = 0;
	if (root == NULL || *root == NULL)
		return ;
	tmp = *root;
	ft_printf(GRN "node %d:\n" RESET, id);
	ft_printf(YEL"node->type: %s\n", get_node_type((*root)->type));
	if (tmp->cmd)
	{
		while (tmp->cmd[i])
		{
			ft_printf(YEL "command %u\n" RESET, i);
			ft_printf(GRN "cmd->token:\n" RESET);
			print_token(&tmp->cmd[i]->token);
			ft_printf(BLU "cmd->redirect:\n" RESET);
			print_token(&tmp->cmd[i]->redirect_token);
			i++;
		}
	}
	if (tmp->left_node != NULL)
	{
		ft_printf(BLU "LEFT_NODE from %d\n"RESET, id);
		print_tree(&tmp->left_node, id + 1);
	}
	if (tmp->right_node != NULL)
	{
		ft_printf(BLU "RIGHT_NODE from %d\n"RESET, id);
		print_tree(&tmp->right_node, id +1);
	}
}
