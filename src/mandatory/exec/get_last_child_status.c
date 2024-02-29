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
	int status;
	int	pid;

	while (1)
	{
		pid = wait(&status);
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);			
		}
		else if (pid < 0)
		{
			break ;
		}
	}
	return (status);
}