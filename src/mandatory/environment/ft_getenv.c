/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:41:54 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/16 15:41:55 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_match_line(const char *line, const char *to_find)
{
	if (line != NULL
		&& (ft_strncmp(line, to_find, ft_strlen(to_find)) == SUCCESS)
		&& line[ft_strlen(to_find)] == '=')
	{
		return (TRUE);
	}
	else
	{
		return (FALSE);
	}
}

static char	*get_variable_line(const char *name, const t_env env)
{
	size_t	var_num;

	var_num = 0;
	while (var_num < env.allocated_size)
	{
		if (is_match_line(env.variables[var_num], name) == TRUE)
		{
			return (env.variables[var_num]);
		}
		++var_num;
	}
	return (NULL);
}

static char	*get_value(const char *line, const char *name)
{
	if (line == NULL)
	{
		return (NULL);
	}
	else
	{
		return ((char *)&line[ft_strlen(name) + 1]);
	}
}

char	**get_line_address(const char *name, const t_env env)
{
	size_t	var_num;

	var_num = 0;
	while (env.variables[var_num] != NULL)
	{
		if (is_match_line(env.variables[var_num], name) == TRUE)
		{
			return (&env.variables[var_num]);
		}
		++var_num;
	}
	return (NULL);
}

char	*ft_getenv(const char *name, const t_env env)
{
	char	*variable_line;

	if (!name)
	{
		return (NULL);
	}
	variable_line = get_variable_line(name, env);
	return (get_value((const char *)variable_line, name));
}

// int	main(int ac, char **av, char **env)
// {
// 	t_env	my_env;
// 	(void)ac;
// 	(void)av;

// 	my_env = create_env((const char **)env);
// 	printf("%s\n", ft_getenv("PWD22", (const t_env)my_env));
// 	ft_free_str_array(my_env.variables);
// 	return (0);
// }