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
	int		error;
	char	*pwd_var_value;
	int		var_num;

	if (env->was_oldpwd_unset == TRUE)
		return (SUCCESS);
	pwd_var_value = ft_getenv("PWD", (const t_env) * env);
	if (pwd_var_value == NULL && env->pwd_unset_time == NEW)
		return (SUCCESS);
	*env = get_expended_env(*env, &error);
	if (error != SUCCESS)
		return (error);
	var_num = 0;
	while (env->variables[var_num] != NULL)
		++var_num;
	if (pwd_var_value == NULL)
		env->variables[var_num] = ft_strjoin("OLDPWD=", old_pwd);
	else
		env->variables[var_num] = ft_strjoin("OLDPWD=", pwd_var_value);
	if (env->variables[var_num] == NULL)
		return (MALLOC_FAIL);
	else
		return (SUCCESS);
}

int	update_existing_oldpwd(const char *old_pwd, t_env *env)
{
	char	*pwd_var_value;
	char	*oldpwd_var_value;
	char	**oldpwd_address;

	pwd_var_value = ft_getenv("PWD", (const t_env) * env);
	if (pwd_var_value == NULL && env->pwd_unset_time == NEW)
	{
		oldpwd_var_value = ft_getenv("OLDPWD", (const t_env) * env);
		oldpwd_var_value[0] = '\0';
		return (SUCCESS);
	}
	oldpwd_address = get_line_address("OLDPWD", (const t_env) * env);
	if (pwd_var_value == NULL && env->pwd_unset_time == OLD)
		oldpwd_var_value = ft_strjoin("OLDPWD=", old_pwd);
	else
		oldpwd_var_value = ft_strjoin("OLDPWD=", pwd_var_value);
	if (oldpwd_var_value == NULL)
		return (MALLOC_FAIL);
	free(*oldpwd_address);
	*oldpwd_address = oldpwd_var_value;
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
		ft_fprintf(2, "minishell: cd: only one argument is required\n");
		return (FAILURE);
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir((const char *)argv[1]) != SUCCESS)
	{
		ft_fprintf(2, "minishell: cd: %s: %s\n", argv[1], strerror(errno));
		return (free(old_pwd), FAILURE);
	}
	new_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL || new_pwd == NULL)
		return (perror("minishell: cd: "),free(old_pwd),
			free(new_pwd), FAILURE);
	if (update_oldpwd(old_pwd, env) == MALLOC_FAIL)
		return (free(old_pwd), free(new_pwd), MALLOC_FAIL);
	if (update_pwd(new_pwd, env) == MALLOC_FAIL)
		return (free(old_pwd), free(new_pwd), MALLOC_FAIL);
	if (env->pwd_unset_time == NEW)
		env->pwd_unset_time = OLD;
	return (free(old_pwd), free(new_pwd), SUCCESS);
}
