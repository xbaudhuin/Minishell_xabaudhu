/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:23:59 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/03/04 11:24:02 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_pwd(t_env new_env)
{
	char	*pwd_str;
	char	*pwd_value;
	char	**null_address;

	pwd_value = getcwd(NULL, 0);
	if (pwd_value == NULL)
	{
		ft_fprintf(2, "minishell: %s\n", strerror(errno));
	}
	pwd_str = ft_strjoin("PWD=", pwd_value);
	if (pwd_str == NULL)
	{
		ft_fprintf(2, "minishell: %s\n", strerror(errno));
	}
	null_address = get_first_null_address((const t_env) new_env);
	*null_address = pwd_str;
	free(pwd_value);
}
