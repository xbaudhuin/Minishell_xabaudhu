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

#include "builtins.h"

static int	is_there_n_option(int argc, const char **argv)
{
	char	*to_compare;
	size_t	bytes_to_compare;

	to_compare = "-n";
	bytes_to_compare = ft_strlen(to_compare) + 1;
	if (argc > 1 && !ft_strncmp(argv[1], to_compare, bytes_to_compare))
	{
		return (TRUE);
	}
	else
	{
		return (FALSE);
	}
}

static void	print_args(int start, int nb_args, const char **av)
{
	int	arg_num;

	arg_num = start;
	while (arg_num < nb_args)
	{
		ft_putstr_fd((char *)av[arg_num], 1);
		++arg_num;
		if (arg_num != nb_args)
		{
			print_space();
		}
	}
}

int	set_start(int nl_option)
{
	int	start;

	if (nl_option == FALSE)
	{
		start = 1;
	}
	else
	{
		start = 2;
	}
	return (start);
}

void	handle_option(int nl_option)
{
	if (nl_option == FALSE)
	{
		print_new_line();
	}
}

int	echo(const char **argv)
{
	int	nb_args;
	int	nl_option;
	int	start;

	nb_args = count_args(argv);
	nl_option = is_there_n_option(nb_args, argv);
	start = set_start(nl_option);
	print_args(start, nb_args, argv);
	handle_option(nl_option);
	return (0);
}

// int	main(int ac, char **av)
// {
	// (void)ac;
	// echo((const char **)av);
// }
// 