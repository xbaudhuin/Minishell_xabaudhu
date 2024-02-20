/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:44:06 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/20 15:44:07 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_last_address(const t_env env)
{
	size_t	var_num;

	var_num = env.allocated_size - 1;
	while (var_num >= 0)
	{
		if (env.variables[var_num] != NULL)
		{
			break ;
		}
		--var_num;
	}
	return (&env.variables[var_num]);
}

static void	swap_address(char **first_add, char **second_add)
{
	char	*temp;

	temp = *first_add;
	*first_add = *second_add;
	*second_add = temp;
}

static void	check_pwd_variable(const char *name, t_env *env)
{
	if (ft_strncmp(name, "PWD", ft_strlen("PWD") + 1) == SUCCESS)
	{
		env->was_pwd_unset = TRUE;
	}
	else if (ft_strncmp(name, "OLDPWD", ft_strlen("OLDPWD") + 1) == SUCCESS)
	{
		env->was_oldpwd_unset = TRUE;
	}
	else
	{
		return ;
	}
}

static int	unset_one_variable(const char *name, t_env *env)
{
	char	**variable_address;
	char	**last_var_address;

	check_pwd_variable(name, env);
	variable_address = get_line_address(name, (const t_env) * env);
	if (variable_address == NULL)
	{
		return (SUCCESS);
	}
	last_var_address = get_last_address((const t_env) * env);
	free(*variable_address);
	*variable_address = NULL;
	swap_address(variable_address, last_var_address);
	return (SUCCESS);
}

int	unset(const char **argv, t_env *env)
{
	size_t	arg_num;

	if (check_option(argv, "unset") == FAILURE)
	{
		return (WRG_OPT);
	}
	arg_num = 1;
	while (argv[arg_num] != NULL)
	{
		unset_one_variable((const char *)argv[arg_num], env);
		++arg_num;
	}
	return (SUCCESS);
}
