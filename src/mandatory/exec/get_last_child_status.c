/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_child_status.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:46:02 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/29 17:46:03 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_last_child_status(pid_t last_pid)
{
	int		code_exit;
	int		exit_status;
	pid_t	pid;

	while (1)
	{
		pid = wait(&code_exit);
		if (pid == last_pid)
		{
			if (WIFEXITED(code_exit))
			{
				exit_status = WEXITSTATUS(code_exit);
			}		
		}
		else if (pid < 0)
		{
			break ;
		}
	}
	return (exit_status);
}
