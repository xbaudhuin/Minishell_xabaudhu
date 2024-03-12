/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:22:37 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/22 15:22:41 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_global;

void	rl_new_prompt(int signal)
{
	if (signal == SIGINT)
	{
		if (g_global != 1)
		{
			write(1, "\n", 1);
			g_global = SIGINT;
		}
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	close_stdin(int signal)
{
	if (signal == SIGINT)
	{
		g_global = 1;
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
}

void	update_while_child(int signal)
{
	if (signal == SIGINT)
	{
		g_global = SIGINT;
	}
}

int	handle_sigint(int option)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof (action));
	if (option == NEW_PROMPT)
	{
		action.sa_handler = &rl_new_prompt;
	}
	else if (option == DEFAULT)
	{
		action.sa_handler = SIG_DFL;
	}
	else if (option == CLOSE_IN)
	{
		action.sa_handler = &close_stdin;
	}
	else
	{
		action.sa_handler = &update_while_child;
	}
	sigaction(SIGINT, &action, NULL);
	return (SUCCESS);
}
