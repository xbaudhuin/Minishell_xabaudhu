/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:51:00 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/13 12:51:02 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_option(const char *arg)
{
	int	char_num;

	char_num = 2;
	if (arg[0] != '-' || arg[1] != 'n' )
	{
		return (FALSE);
	}
	while (arg[char_num] != '\0')
	{
		if (arg[char_num] != 'n')
		{
			return (FALSE);
		}
		++char_num;
	}
	return (TRUE);
}

static void	display_args(int start, const char **av)
{
	int	arg_num;

	arg_num = start;
	while (av[arg_num] != NULL)
	{
		ft_putstr_fd((char *)av[arg_num], STDOUT_FILENO);
		++arg_num;
		if (av[arg_num] != NULL)
		{
			print_space();
		}
	}
}

void	handle_option(int start)
{
	if (start == 1)
	{
		print_new_line();
	}
}

int	get_start(const char **argv)
{
	int	start;

	start = 1;
	while (argv[start] != NULL)
	{
		if (is_n_option((const char *)argv[start]) == FALSE)
		{
			break ;
		}
		++start;
	}
	return (start);
}

int	echo(const char **argv)
{
	int	start;

	start = get_start(argv);
	display_args(start, argv);
	handle_option(start);
	return (SUCCESS);
}