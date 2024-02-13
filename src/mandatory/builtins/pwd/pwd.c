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

static void	handle_error(void)
{
	perror("pwd");
}

int	pwd(const char **argv)
{
	const char	*pwd_str;


	pwd_str = getcwd(NULL, 0);
	if (pwd_str == NULL)
	{
		handle_error();
		return (FAILURE);
	}
	else
	{
		print_working_dir(pwd_str);
		return (SUCESS);
	}
}

int	main(int ac, char **av)
{
	pwd((const char **)av);
}