/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:09:02 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/27 19:09:03 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	launch_type()
{

}

int	launch_node(t_command **cmd, t_env *env)
{
	t_exec_cmd *cmd;

	av = (expand(cmd[0]->token));
}