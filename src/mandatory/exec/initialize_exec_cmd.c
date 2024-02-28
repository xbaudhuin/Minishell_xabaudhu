/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_exec_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:36:42 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/28 15:36:42 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nb_cmd(t_command **cmd)
{
	int	nb_cmd;

	nb_cmd = 0;
	while (cmd[nb_cmd] != NULL)
	{
		++nb_cmd;
	}
	return (nb_cmd);
}

static void	free_exec_cmd(t_exec_cmd **exec_cmd)
{
	int	cmd_num;

	cmd_num = 0;
	while (exec_cmd[cmd_num] != NULL)
	{
		free(exec_cmd[cmd_num]);
		++cmd_num;
	}
	free(exec_cmd);
}

static t_exec_cmd	**alloc_exec_cmd(int nb_cmd)
{
	t_exec_cmd	**exec_cmd;
	int			cmd_num;

	exec_cmd = ft_calloc(sizeof (*exec_cmd), nb_cmd + 1);
	if (exec_cmd == NULL)
	{
		ft_fprintf(2, "minishell: malloc error in launch_node\n");
		return (NULL);
	}
	cmd_num = 0;
	while (cmd_num < nb_cmd)
	{
		exec_cmd[cmd_num] = ft_calloc(sizeof (**exec_cmd), 1);
		if (exec_cmd == NULL)
		{
			ft_fprintf(2, "minishell: malloc error in launch_node\n");
			free_exec_cmd(exec_cmd);
			return (NULL);
		}
		++cmd_num;
	}
	return (exec_cmd);
}

t_exec_cmd	**initialize_exec_cmd(t_command **cmd)
{
	t_exec_cmd	**exec_cmd;
	int			nb_cmd;
	int			cmd_num;

	nb_cmd = get_nb_cmd(cmd);
	exec_cmd = alloc_exec_cmd(nb_cmd);
	if (exec_cmd == NULL)
	{
		return (NULL);
	}
	cmd_num = 0;
	while (cmd_num < nb_cmd)
	{
		exec_cmd[cmd_num]->argv = get_cmd_argv(cmd[cmd_num]);
		if (exec_cmd[cmd_num]->argv == NULL)
		{
			free_exec_cmd(exec_cmd);
			return (NULL);
		}
		++cmd_num;
	}
	return (exec_cmd);
}
