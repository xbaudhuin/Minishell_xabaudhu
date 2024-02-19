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

#include "environment.h"

static int	is_match_line(const char *line, const char *to_find)
{
	if (line != NULL
		&& (ft_strncmp(line, to_find, ft_strlen(to_find)) == SUCCESS))
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
	char	*to_find;

	var_num = 0;
	to_find = ft_strjoin(name, "=");
	if (to_find == NULL)
	{
		return (NULL);
	}
	while (var_num < env.allocated_size)
	{
		if (is_match_line(env.variables[var_num], to_find) == TRUE)
		{
			return (free(to_find), env.variables[var_num]);
		}
		++var_num;
	}
	return (free(to_find), NULL);
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

char	*ft_getenv2(const char *name, const t_env env)
{
	char	*variable_line;

	if (!name)
	{
		return (NULL);
	}
	variable_line = get_variable_line(name, env);
	return (variable_line);	
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
// 	printf("%s\n", ft_getenv("OHOH", (const t_env)my_env));
// 	ft_free_str_array(my_env.variables);
// 	return (0);
// }