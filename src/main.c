/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:16:18 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/03/04 12:29:18 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global;

static int	check_redirection(void)
{
	if (isatty(STDIN_FILENO) == FALSE || isatty(STDOUT_FILENO) == FALSE
		|| isatty(STDERR_FILENO) == FALSE)
	{
		return (FAILURE);
	}
	else
	{
		return (SUCCESS);
	}
}

int	main(int ac, char **av, char **main_env)
{	
	g_global = 0;
	(void)av;
	if (ac != 1)
	{
		ft_fprintf(2, "minishell: too many arguments\n");
		exit(2);
	}
	if (check_redirection() == FAILURE)
	{
		ft_fprintf(2, "minishell: does not support file redirections\n");
		exit(2);
	}
	minishell((const char **)main_env);
}
