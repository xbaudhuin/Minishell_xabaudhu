/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:49:46 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/16 10:49:48 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	is_pwd_exist(void)
{
	if (getenv("PWD") == NULL)
	{
		return (FALSE);
	}
	else
	{
		return (TRUE);
	}
}

static size_t	get_malloc_size(const char **main_env)
{
	size_t	malloc_size;

	malloc_size = ft_strarraylen(main_env) + 1;
	if (is_pwd_exist() == FALSE)
	{
		++malloc_size;
	}
	return (malloc_size);
}

static void	add_pwd(t_env new_env)
{
	char	*pwd_str;
	char	*env_result;

	if (is_pwd_exist() == FALSE)
	{
		env_result = getcwd(NULL, 0);
		pwd_str = ft_strjoin("PWD=", env_result);
		new_env.variables[new_env.allocated_size - 2] = pwd_str;
		free(env_result);
	}
}

static char	**create_env_var(const char **main_env, size_t malloc_size)
{
	char	**env_variables;
	int		var_num;

	env_variables = ft_calloc(sizeof (*env_variables), malloc_size);
	if (env_variables == NULL)
	{
		return (NULL);
	}
	var_num = 0;
	while (main_env[var_num] != NULL)
	{
		env_variables[var_num] = ft_strdup(main_env[var_num]);
		if (env_variables[var_num] == NULL)
		{
			ft_free_str_array(env_variables);
			return (NULL);
		}
		++var_num;
	}
	return (env_variables);
}

t_env	create_env(const char **main_env)
{
	t_env	new_env;

	new_env.allocated_size = get_malloc_size(main_env);
	new_env.variables = create_env_var(main_env, new_env.allocated_size);
	add_pwd(new_env);
	return (new_env);
}

// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	//char *pwd = getenv("PWD");
// 	//ft_bzero(pwd, ft_strlen(pwd));
// 	t_env new_env = create_env((const char **)env);
// 	size_t	i = 0;
// 	while (i < new_env.allocated_size)
// 	{
// 		if (new_env.variables[i])
// 		{
// 			printf("%s\n", new_env.variables[i]);
// 		}
// 		++i;
// 	}
// 	ft_free_str_array(new_env.variables);
// }