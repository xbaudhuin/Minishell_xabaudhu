/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:50:27 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/19 10:50:27 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_name_valid(const char *arg)
{
	size_t	char_num;

	if (is_underscore(arg[0]) == FALSE && ft_isalpha(arg[0]) == FALSE)
	{
		return (FALSE);
	}
	char_num = 1;
	while (arg[char_num] != '\0' && arg[char_num] != '=')
	{
		if (is_underscore(arg[char_num]) == FALSE
				&& ft_isalnum(arg[char_num]) == FALSE)
		{
			return (FALSE);
		}
		++char_num;
	}
	return (TRUE);
}

int	check_option(const char **argv)
{
	if (count_args(argv) > 1 && ft_strlen(argv[1] > 1) && argv[1][0] == '-')
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: export: -%c: invalid option", argv[1][1]);
		return (FAILURE);
	}
	else
	{
		return (SUCCESS);
	}
}

void	export_one_arg(const char *arg, int *exit_status)
{
	if (is_name_valid(arg) == FALSE)
	{
		*exit_status = FAILURE;
		return ;
	}
	if (is_equal_exist(arg) == FALSE)
	{
		return ;
	}
	if (ft_getenv())
}

int	export(const char **argv, t_env *env)
{
	int	exit_status;
	int	arg_num;

	exit_status = SUCCESS;
	if (check_option(argv) == FAILURE)
	{
		return (WRG_OPT);
	}
	while (argv[arg_num] != NULL)
	{
		export_one_arg(argv[arg_num], &exit_status);
		++arg_num;
	}
	return (exit_status);
}

int	main(int ac, char **av, char **env)
{
	return (SUCCESS);
}