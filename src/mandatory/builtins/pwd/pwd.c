/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:22:02 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/13 17:22:14 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_working_dir(const char *pwd_str)
{
	ft_putstr_fd((char *)pwd_str, 1);
	print_new_line();
}

static int	is_there_wrong_option(const char **args)
{
	int	arg_num;

	arg_num = 0;
	while (args[arg_num])
	{
		if (args[arg_num][0] == '-' && args[arg_num][1] != '\0')
		{
			return (args[arg_num][1]);
		}		
		++arg_num;
	}
	return (FALSE);
}

static void	print_option_error(int wrong_option)
{
	ft_fprintf(2, "minishell: pwd: -%c: invalid option\n", wrong_option);
}

int	pwd(const char **argv)
{
	const char	*pwd_str;
	int			wrong_option;

	wrong_option = is_there_wrong_option(argv);
	if (wrong_option != FALSE)
	{
		print_option_error(wrong_option);
		return (2);
	}
	pwd_str = getcwd(NULL, 0);
	if (pwd_str == NULL)
	{
		perror("getcwd");
		return (errno);
	}
	else
	{
		print_working_dir(pwd_str);
		return (SUCCESS);
	}
}

// int	main(int ac, char **av)
// {
	// (void)ac;
	// return (pwd((const char **)av));
// }
