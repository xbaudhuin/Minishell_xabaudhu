/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:29:25 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/20 17:29:26 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd(const char *new_pwd, t_env *env)
{
	char	**pwd_line_address;
	char	*new_pwd_line_value;

	pwd_line_address = get_line_address("PWD", (const t_env) * env);
	if (pwd_line_address == NULL)
	{
		return (SUCCESS);
	}
	new_pwd_line_value = ft_strjoin("PWD=", new_pwd);
	if (new_pwd_line_value == NULL)
	{
		return (MALLOC_FAIL);
	}
	free(*pwd_line_address);
	*pwd_line_address = new_pwd_line_value;
	return (SUCCESS);
}

int	update_null_oldpwd(const char *old_pwd, t_env *env)
{
	if (env->was_oldpwd_unset == TRUE)
	{
		return (SUCCESS);
	}

}

int	update_existing_oldpwd(const char *old_pwd, t_env *env)
{
	return (SUCCESS);
}

int	update_oldpwd(const char *old_pwd, t_env *env)
{
	char	**old_pwd_line_address;
	
	old_pwd_line_address = get_line_address("OLDPWD", (const t_env) * env);
	if (old_pwd_line_address == NULL)
	{
		return (update_null_oldpwd(old_pwd, env));
	}
	else
	{
		return (update_existing_oldpwd(old_pwd, env));
	}
}

int	cd(const char **argv, t_env *env)
{
	char	*old_pwd;
	char	*new_pwd;

	if (count_args(argv) != 2)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: cd: only one argument is required\n");
		return (FAILURE);
	}
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
	{
		perror("minishell: cd: ");
		return (FAILURE);
	}
	if (chdir((const char *)argv[1]) != SUCCESS)
	{
		free(old_pwd);
		perror("minishell: cd: ");
		return (FAILURE);
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		free(old_pwd);
		perror("minishell: cd: ");
		return (FAILURE);
	}
	if (update_oldpwd(old_pwd, env) == MALLOC_FAIL)
	{
		return (free(old_pwd), free(new_pwd), MALLOC_FAIL);
	}
	if (update_pwd(new_pwd, env) == MALLOC_FAIL)
	{
		return (free(old_pwd), free(new_pwd), MALLOC_FAIL);
	}
	if (env->pwd_unset_time == NEW)
	{
		env->pwd_unset_time = OLD;
	}
	return (free(old_pwd),free(new_pwd) , SUCCESS);
}
 