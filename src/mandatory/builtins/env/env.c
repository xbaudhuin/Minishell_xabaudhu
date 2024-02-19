/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:21:49 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/17 16:21:51 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_line(const char *line)
{
	printf("%s\n", line);
}

static void	print_env(const t_env env)
{
	size_t	var_num;

	var_num = 0;
	while (env.variables[var_num] != NULL)
	{
		print_line((const char *)env.variables[var_num]);
		++var_num;
	}
}

int	env(const char **argv, const t_env env)
{
	if (count_args(argv) != 1)
	{
		ft_putstr_fd("env builtin take no arguments and no option\n",
			STDERR_FILENO);
		return (FAILURE);
	}
	print_env(env);
	return (SUCCESS);
}

// int	main(int ac, char **av, char **main_env)
// {
// 	t_env	my_env;

// 	(void)ac;
// 	my_env = create_env((const char **)main_env);
// 	env((const char **)av, (const t_env)my_env);
// 	free_env(my_env);
// 	return (SUCCESS);
// }