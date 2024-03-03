/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:59:29 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/03/01 14:59:29 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_first_cmd(t_data *data)
{
	int	exit_status;

	exit_status = SUCCESS;
	close(data->pipe_fd[READ_SIDE]);
	if (dup2(data->pipe_fd[WRITE_SIDE], STDOUT_FILENO) == INVALID_FD)
	{
		exit_status = FAILURE;
	}
	close(data->pipe_fd[WRITE_SIDE]);
	return (exit_status);
}

static int	redirect_last_cmd(t_data *data)
{
	int	exit_status;

	exit_status = SUCCESS;
	if (dup2(data->tmp_fd, STDIN_FILENO) == INVALID_FD)
	{
		exit_status = FAILURE;
	}
	close(data->tmp_fd);
	return (exit_status);
}

static int	redirect_middle_cmd(t_data *data)
{
	int	exit_status;

	exit_status = SUCCESS;
	close(data->pipe_fd[READ_SIDE]);
	if (dup2(data->pipe_fd[WRITE_SIDE], STDOUT_FILENO) == INVALID_FD
		|| dup2(data->tmp_fd, STDIN_FILENO) == INVALID_FD)
	{
		exit_status = FAILURE;
	}
	close(data->pipe_fd[WRITE_SIDE]);
	close(data->tmp_fd);	
	return (exit_status);
}

int	set_pipe_redirection(t_data *data, int cmd_num)
{
	int	exit_status;

	exit_status = SUCCESS;
	if (cmd_num == 0)
	{
		exit_status = redirect_first_cmd(data);
	}
	else if (cmd_num == data->nb_cmd - 1)
	{
		exit_status = redirect_last_cmd(data);
	}
	else
	{
		exit_status = redirect_middle_cmd(data);
	}
	return (exit_status);
}