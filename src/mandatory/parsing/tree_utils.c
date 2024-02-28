/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:35:31 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/28 18:40:57 by xabaudhu         ###   ########.fr       */
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
