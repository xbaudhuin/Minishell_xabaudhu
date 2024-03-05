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

extern int	global;

void	rl_new_prompt(int signal)
{
	if (signal == SIGINT)
	{
		global = SIGINT;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	close_stdin(int signal)
{
	if (signal == SIGINT)
	{
		global = SIGINT;
		close(STDIN_FILENO);
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
	else
	{
		action.sa_handler = &close_stdin;
	}
	sigaction(SIGINT, &action, NULL);
	return (SUCCESS);
}
