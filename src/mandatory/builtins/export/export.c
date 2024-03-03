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

#include "minishell.h"

static char	*get_name(const char *arg)
{
	size_t	char_num;
	char	*name;

	char_num = 0;
	while (arg[char_num] != '=' && arg[char_num] != '\0')
	{
		++char_num;
	}
	name = malloc(sizeof (*name) * (char_num + 1));
	if (name == NULL)
	{
		return (NULL);
	}
	name[char_num] = '\0';
	while (char_num > 0)
	{
		--char_num;
		name[char_num] = arg[char_num];
	}
	return (name);
}

static int	add_variable(const char *arg, char *name, t_env *env)
{
	int	exit_status;
	int	var_num;

	*env = get_expended_env(*env, &exit_status);
	if (exit_status != SUCCESS)
	{
		free(name);
		ft_fprintf(2, RED"Fail malloc in export builtin\n"RESET);
		return (exit_status);
	}
	var_num = 0;
	while (env->variables[var_num] != NULL)
	{
		++var_num;
	}
	env->variables[var_num] = ft_strdup(arg);
	if (env->variables[var_num] == NULL)
	{
		exit_status = MALLOC_FAIL;
	}
	free(name);
	return (exit_status);
}

static int	replace_variable(const char *arg, char *name, t_env *env)
{
	char	*new_line;
	char	**line_address;

	new_line = ft_strdup(arg);
	if (new_line == NULL)
	{
		return (MALLOC_FAIL);
	}
	line_address = get_line_address((const char *)name, (const t_env) * env);
	free(*line_address);
	*line_address = new_line;
	free(name);
	return (SUCCESS);
}

static int	export_one_arg(const char *arg, t_env *env)
{
	char	*name;

	if (is_var_name_valid(arg) == FALSE)
	{
		ft_fprintf(2, "minishell: export: '%s': not a valid identifier\n", arg);
		return (FAILURE);
	}
	if (is_equal_exists(arg) == FALSE)
	{
		return (SUCCESS);
	}
	name = get_name(arg);
	if (name == NULL)
	{
		return (MALLOC_FAIL);
	}
	if (ft_getenv(name, *env) == NULL)
	{
		return (add_variable(arg, name, env));
	}
	else
	{
		return (replace_variable(arg, name, env));
	}	
}

int	export(const char **argv, t_env *env)
{
	int	exit_status;
	int	err_return;
	int	arg_num;

	exit_status = SUCCESS;
	if (check_option(argv, "export") == FAILURE)
	{
		return (WRG_OPT);
	}
	arg_num = 1;
	while (argv[arg_num] != NULL)
	{
		err_return = export_one_arg(argv[arg_num], env);
		if (err_return == MALLOC_FAIL)
		{
			ft_fprintf(2, "minishell: a call to malloc failed in export");
			return (MALLOC_FAIL);
		}
		else if (err_return == FAILURE)
		{
			exit_status = FAILURE;
		}
		++arg_num;
	}
	return (exit_status);
}