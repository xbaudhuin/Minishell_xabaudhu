/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:46:18 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/03/01 14:46:18 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_pipe(t_data *data, int cmd_num)
{
	if (cmd_num > 0)
	{
		if (cmd_num > 1)
			close(data->tmp_fd);
		close(data->pipe_fd[WRITE_SIDE]);
		data->tmp_fd = data->pipe_fd[READ_SIDE];
	}
	if (cmd_num < data->nb_cmd - 1)
	{
		if (pipe(data->pipe_fd) == -1)
		{
			ft_fprintf(2, "minishell: launch_pipeline: %s\n", strerror(errno));
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
