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

extern int	global;

int	get_last_child_status(pid_t last_pid)
{
	int		code_exit;
	int		exit_status;
	int		last_received;
	pid_t	pid;

	last_received = FALSE;
	exit_status = SUCCESS;
	while (1)
	{
		pid = waitpid((pid_t)-1, &code_exit, WNOHANG);
		if (pid == last_pid)
		{	
			if (WIFSIGNALED(code_exit))
			{
				exit_status = WTERMSIG(code_exit);
				if (exit_status == SIGQUIT)
				{
					ft_fprintf(2, "Quit (core dumped)\n");
					exit_status = 131;
				}
				else if (exit_status == SIGINT)
					exit_status = 130;
			}
			else if (WIFEXITED(code_exit) == TRUE)
			{
				last_received = TRUE;
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
