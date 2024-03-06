/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:44:15 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/28 19:44:17 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data data)
{
	free_exec_cmd(data.exec_cmd);
	free_env(data.env);
	free_tree(go_to_root(data.root));
	rl_clear_history();
}
