/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:32:44 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/22 18:32:45 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define INVALID_FD -1
# define TTY -2

enum e_launch_type
{
	LAUNCH_CMD = 1,
	LAUNCH_BUILTIN = 2,
	LAUNCH_PIPELINE = 3,
};

int		open_cmd_files(t_token *redirect_token, t_exec_cmd *cmd);
char	*get_cmd_path(const char *cmd_first_arg, const t_env env, int *exit_status);
char	**get_cmd_argv(t_command *cmd);
void	end_process(t_node **root, t_env *env);
int		test_fork(t_command *cmd, t_env *env, t_node **root);
int		launch_tree(t_node *root, t_env *env);

#endif
