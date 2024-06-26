/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:55:53 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/26 18:55:54 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_process(t_exec_cmd *exec_cmd, t_data data, int exit_status)
{
	close_cmd_files(exec_cmd);
	free_data(data);
	exit(exit_status);
}
