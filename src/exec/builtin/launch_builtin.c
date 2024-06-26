/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:08:33 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/28 16:08:34 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	restore_std(int save_std[2])
{
	if (dup2(save_std[0], STDIN_FILENO) == INVALID_FD)
	{
		close(save_std[0]);
		close(save_std[1]);
		ft_fprintf(2, "minishell: launch_builtin: %s\n", strerror(errno));
		return (FAILURE);
	}
	if (dup2(save_std[1], STDOUT_FILENO) == INVALID_FD)
	{
		close(save_std[0]);
		close(save_std[1]);
		ft_fprintf(2, "minishell: launch_builtin: %s\n", strerror(errno));
		return (FAILURE);
	}
	close(save_std[0]);
	close(save_std[1]);
	return (SUCCESS);
}

static int	launch_rigth_builtin(const char **argv,
				t_data *data, int buildin_type)
{
	if (buildin_type == EXPORT)
		return (export(argv, data->env));
	else if (buildin_type == ENV)
		return (env(argv, (const t_env) * data->env));
	else if (buildin_type == UNSET)
		return (unset(argv, data->env));
	else if (buildin_type == CD)
		return (cd(argv, data->env));
	else if (buildin_type == PWD)
		return (pwd(argv));
	else if (buildin_type == EXIT)
		return (builtin_exit(argv, data->env, data));
	else if (buildin_type == ECHO)
		return (echo(argv));
	return (SUCCESS);
}

int	launch_builtin(t_exec_cmd *exec_cmd, t_token *redirect_token, t_data *data)
{
	int			exit_status;
	const char	**arg_builtin;

	if (set_builtin_redirection(exec_cmd,
			redirect_token, data->save_std) == FAILURE)
	{
		return (FAILURE);
	}
	arg_builtin = (const char **)exec_cmd->argv;
	exit_status = launch_rigth_builtin(arg_builtin,
			data, is_builtin(arg_builtin));
	if (restore_std(data->save_std) == FAILURE)
	{
		ft_fprintf(2, "minishell: builtin: can not restore std\n");
		return (FAILURE);
	}
	return (exit_status);
}
