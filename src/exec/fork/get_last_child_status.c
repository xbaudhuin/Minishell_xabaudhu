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

extern int	g_global;

static int	get_sig_status(int code_exit)
{
	int	status;

	status = WTERMSIG(code_exit);
	if (status == SIGQUIT)
	{
		ft_fprintf(2, "Quit (core dumped)\n");
		status = 131;
	}
	else if (status == SIGINT)
	{
		status = 130;
	}
	else
	{
		status += 128;
	}
	return (status);
}

static int	get_exit_status(int code_exit)
{
	int	exit_status;

	exit_status = SUCCESS;
	if (WIFSIGNALED(code_exit))
	{
		exit_status = get_sig_status(code_exit);
	}
	else if (WIFEXITED(code_exit) == TRUE)
	{
		exit_status = WEXITSTATUS(code_exit);
	}
	return (exit_status);
}

int	get_last_child_status(pid_t last_pid)
{
	int		code_exit;
	int		exit_status;
	pid_t	pid;

	exit_status = SUCCESS;
	while (1)
	{
		pid = waitpid((pid_t) - 1, &code_exit, WNOHANG);
		if (pid == last_pid)
		{
			exit_status = get_exit_status(code_exit);
		}
		else if (pid < 0)
		{
			break ;
		}
	}
	return (exit_status);
}
