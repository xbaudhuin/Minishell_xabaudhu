/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:38:13 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/26 15:38:14 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_slash(char *path)
{
	char	*path_with_slash;

	path_with_slash = ft_strjoin(path, "/");
	if (path_with_slash == NULL)
	{
		ft_fprintf(2, "minishell: a malloc failed constructing cmd path\n");
	}
	free(path);
	return (path_with_slash);
}

char	**split_and_add_slash(char *env_paths_line)
{
	char	**env_paths;
	int		path_num;
	char	*path_with_slash;

	env_paths = ft_split(env_paths_line, ':');
	if (env_paths == NULL)
	{
		ft_fprintf(2, "minishell: a malloc failed constructing cmd path\n");
		return (env_paths);
	}
	path_num = 0;
	while (env_paths[path_num] != NULL)
	{
		path_with_slash = add_slash(env_paths[path_num]);
		if (path_with_slash == NULL)
		{
			free_split(env_paths);
			return (NULL);
		}
		env_paths[path_num] = path_with_slash;
		++path_num;
	}
	return (env_paths);
}

char	**get_env_paths(const t_env env)
{
	char	**env_paths;
	char	*env_paths_line;

	env_paths_line = ft_getenv("PATH", env);
	if (env_paths_line == NULL)
	{
		return (NULL);
	}
	env_paths = split_and_add_slash(env_paths_line);
	return (env_paths);
}

char	*construct_path(const char *cmd_first_arg, const t_env env, int *exit_status)
{
	char	**env_paths;
	char	*cmd_path;
	int		path_num;

	env_paths = get_env_paths(env);
	if (env_paths == NULL)
		return (NULL);
	path_num = 0;
	while (env_paths[path_num] != NULL)
	{
		cmd_path = ft_strjoin(env_paths[path_num], cmd_first_arg);
		if (cmd_path == NULL)
		{
			ft_fprintf(2, "minishell: a malloc failed constructing cmd path\n");
			return (free_split(env_paths), NULL);
		}
		if (access(cmd_path, F_OK) == SUCCESS)
		{
			return (free_split(env_paths), cmd_path);
		}
		free(cmd_path);
		++path_num;
	}
	ft_fprintf(2, "%s: command not found\n", cmd_first_arg);
	*exit_status = 127;
	return (free_split(env_paths), NULL);
}

char	*get_cmd_path(const char *cmd_first_arg, const t_env env, int *exit_status)
{
	char	*cmd_path;

	*exit_status = SUCCESS;
	if (ft_getenv("PATH", env) == NULL)
	{
		ft_fprintf(2, "%s: command not found\n", cmd_first_arg);
		*exit_status = 127;
		return (NULL);
	}
	if (ft_strchr(cmd_first_arg, '/') != NULL)
	{
		cmd_path = ft_strdup(cmd_first_arg);
		if (cmd_path == NULL)
		{
			ft_fprintf(2, "minishell: a malloc failed constructing cmd path\n");
			*exit_status = FAILURE;
		}
		return (cmd_path);
	}
	else
	{
		return (construct_path(cmd_first_arg, env, exit_status));
	}
}
