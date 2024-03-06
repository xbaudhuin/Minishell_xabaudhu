/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:30:42 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/22 18:30:43 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_cmd(t_exec_cmd *exec_cmd, t_token *redirect_token, t_data data)
{
	pid_t	pid;
	pid_t	pgid;

	pid = fork();
	if (pid == -1)
	{
		return (FAILURE);
	}
	else if (pid == 0)
	{
		handle_sigquit(FALSE);
		handle_sigint(DEFAULT);
		execute_a_cmd(exec_cmd, redirect_token, data);
	}
	pgid = pid;
	return (get_last_child_status(pid));
}
