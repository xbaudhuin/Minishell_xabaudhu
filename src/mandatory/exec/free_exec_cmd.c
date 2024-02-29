/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:53:53 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/28 18:58:29 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec_cmd(t_exec_cmd **exe_cmd)
{
	int	cmd_num;

	cmd_num = 0;
	while (exe_cmd[cmd_num] != NULL)
	{
		free_split(exe_cmd[cmd_num]->argv);
		free(exe_cmd[cmd_num]->path);
		free(exe_cmd[cmd_num]);
		++cmd_num;
	}
	free(exe_cmd);
}
