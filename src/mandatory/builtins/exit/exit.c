/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:01:15 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/21 18:01:16 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_save_std(int save_std[2])
{
	if (save_std[STDIN_FILENO] != INVALID_FD)
	{
		close(save_std[STDIN_FILENO]);
	}
	if (save_std[STDOUT_FILENO] != INVALID_FD)
	{
		close(save_std[STDOUT_FILENO]);
	}	
}

static void	free_all(t_env *env, t_data *data)
{
	free_env(env);
	if (data != NULL)
	{
		free_exec_cmd(data->exec_cmd);
		free_tree(go_to_root(data->root));
		close_save_std(data->save_std);
	}
}

static void	exit_after_rl(t_env *env, t_data *data)
{
	free_all(env, data);
	exit(env->exit_status);
}

static int	get_exit_arg(const char *arg)
{
	unsigned char	exit_arg;

	if (is_exit_arg_valid(arg) == FALSE)
	{
		exit_arg = 2;
		ft_fprintf(2, "minishell: exit: %s: numeric argument required", arg);
	}
	else
	{
		exit_arg = ft_atoi(arg);
	}
	return (exit_arg);
}

int	builtin_exit(const char **argv, t_env *env, t_data *data)
{
	int	nb_args;

	printf("exit\n");
	if (argv == NULL)
		exit_after_rl(env, data);
	nb_args = count_args(argv);
	if (nb_args > 2)
	{
		ft_fprintf(2, "minishell: exit: too many arguments\n");
		return (FAILURE);
	}
	if (nb_args == 2)
	{
		env->exit_status = get_exit_arg((const char *) argv[1]);
	}
	free_all(env, data);
	exit(env->exit_status);
	return (FAILURE);
}
