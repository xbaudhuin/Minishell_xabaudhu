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

int	cd(const char **argv, t_env *env)
{
	char	*old_pwd;
	char	*new_pwd;
	if (count_args(argv != 2))
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
	free(old_pwd);
	free(new_pwd);
	return (SUCCESS);
}
