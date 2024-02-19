/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_empty_address.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:08:34 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/16 20:08:36 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static int	is_env_full(const t_env env)
{
	size_t	var_num;

	var_num = 0;
	while (var_num < env.allocated_size - 1)
	{
		if (env.variables[var_num] == NULL)
		{
			return (FALSE);
		}
		++var_num;
	}
	return (TRUE);
}

static size_t	extanded_size(const t_env old_env)
{
	return (old_env.allocated_size + 1);
}

static char	**set_new_variable_table(const size_t new_allocated_size)
{
	char	**new_table;

	new_table = ft_calloc(new_allocated_size, sizeof (*new_table));
	return (new_table);
}

static char	**copy_old_env(t_env old_env,
		const size_t new_allocated_size)
{
	char	**new_table;
	size_t	var_num;

	new_table = set_new_variable_table(new_allocated_size);
	if (new_table == NULL)
	{
		return (NULL);
	}
	var_num = 0;
	while (var_num < old_env.allocated_size)
	{
		new_table[var_num] = old_env.variables[var_num];
		++var_num;
	}
	new_table[var_num] = NULL;
	free(old_env.variables);
	return (new_table);
}

t_env	get_expended_env(const t_env old_env, int *ext_sts)
{
	t_env	new_env;
	size_t	new_allocated_size;

	if (is_env_full(old_env) == FALSE)
	{
		return (old_env);
	}
	new_allocated_size = extanded_size(old_env);
	new_env.allocated_size = new_allocated_size;
	new_env.variables = copy_old_env(old_env,
			(const size_t) new_allocated_size);
	if (new_env.variables == NULL)
	{
		*ext_sts = MALLOC_FAIL;
		return ((t_env)old_env);
	}
	return (new_env);
}

// int main(int ac, char **av, char **env)
// {
// 	t_env	my_env;

// 	(void)ac;
// 	(void)av;
// 	my_env = create_env((const char **)env);
// 	size_t num = 0;
// 	printf("env alloc size = %zu\n\n", my_env.allocated_size);
// 	printf("is env full = %d\n\n", is_env_full(my_env));
// 	while (num < my_env.allocated_size)
// 	{
// 		printf("%s\n", my_env.variables[num]);
// 		++num;
// 	}
// 	my_env = get_expended_env(my_env);
// 	num = 0;
// 	printf("env alloc size = %zu\n\n", my_env.allocated_size);
// 	printf("is env full = %d\n\n", is_env_full(my_env));
// 	while (num < my_env.allocated_size)
// 	{
// 		printf("%s\n", my_env.variables[num]);
// 		++num;
// 	}
// 	free_env(my_env);
// 	return (0);
// }
