/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:32:44 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/28 21:04:55 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define INVALID_FD -1
# define TTY -2

# define READ_SIDE 0
# define WRITE_SIDE 1

enum e_launch_type
{
	LAUNCH_CMD = 1,
	LAUNCH_BUILTIN = 2,
	LAUNCH_PIPELINE = 3,
};

int			open_cmd_files(t_token *redirect_token, t_exec_cmd *cmd);
char		*get_cmd_path(const char *cmd_first_arg,
				const t_env env, int *exit_status);
char		**get_cmd_argv(const t_command *cmd);
void		end_process(t_exec_cmd *exec_cmd, t_data data, int exit_status);
int			launch_tree(t_node *root, t_env *env);
int			launch_node(t_command **cmd, t_env *env, t_node *root);
t_exec_cmd	**initialize_exec_cmd(const t_command **cmd);
int			launch_cmd(t_exec_cmd *exec_cmd, t_token *redirect_token,
				t_data data);
int			launch_builtin(t_exec_cmd *exec_cmd, t_token *redirect_token,
				t_data *data);
int			launch_pipeline(t_command **cmd, t_exec_cmd **exec_cmd,
				t_data data);
int			set_builtin_redirection(t_exec_cmd *exec_cmd,
				t_token *redirect_token, int save_std[2]);
void		free_exec_cmd(t_exec_cmd **exe_cmd);
void		free_data(t_data data);
int			get_last_child_status(pid_t last_pid);
int			set_cmd_redirection(t_exec_cmd *cmd);
int			open_pipe(t_data *data, int cmd_num);
int			close_cmd_files(t_exec_cmd *cmd);
int			set_pipe_redirection(t_data *data, int cmd_num);
void		execute_a_cmd(t_exec_cmd *exec_cmd, t_token *redirect_token,
				t_data data);
int			is_stdin(const char *path);
int			is_stdout(const char *path);
char		*construct_path(const char *cmd_first_arg,
				const t_env env, int *exit_status);

#endif
