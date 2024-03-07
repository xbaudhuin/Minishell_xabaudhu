/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:56:16 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/07 19:45:35 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_token(t_command **cmd, const t_env env)
{
	if (cmd == NULL)
		return (SUCCESS);
	if (expand_dollar(cmd, env) == FAILURE)
		return (FAILURE);
	if (expand_wildcard(cmd) == FAILURE)
		return (FAILURE);
	trim_quotes_all(cmd);
	return (SUCCESS);
}
