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

static char	*get_verified_path(const char *arg_path, int *exit_status)
{
	char	*cmd_path;

	if (access(arg_path, F_OK) == -1)
	{
		ft_fprintf(2, "minishell: %s: %s\n", arg_path, strerror(errno));
		*exit_status = 127;
		return (NULL);
	}
	cmd_path = ft_strdup(arg_path);
	if (cmd_path == NULL)
	{
		ft_fprintf(2, "minishell: a malloc failed constructing cmd path\n");
		*exit_status = FAILURE;
	}
	return (cmd_path);
}

char	*get_cmd_path(const char *cmd_first_arg,
			const t_env env, int *exit_status)
{
	*exit_status = SUCCESS;
	if (ft_strchr(cmd_first_arg, '/') != NULL)
	{
		return (get_verified_path(cmd_first_arg, exit_status));
	}
	if (ft_getenv("PATH", env) == NULL || ft_strlen(cmd_first_arg) == 0)
	{
		ft_fprintf(2, "minishell: %s: no such file or directory\n",
			cmd_first_arg);
		*exit_status = 127;
		return (NULL);
	}
	else
		return (construct_path(cmd_first_arg, env, exit_status));
}
