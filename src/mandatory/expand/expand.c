/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:56:16 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/03 13:29:11 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_token(t_command **cmd)
{
	if (cmd == NULL)
		return (SUCCESS);
	if (expand_dollar(cmd) == FAILURE)
		return (FAILURE);
	//if (expand_wildcard(cmd) == FAILURE)
	//	return (FAILURE);
	return (SUCCESS);
}
