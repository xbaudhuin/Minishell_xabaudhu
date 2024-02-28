/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:30:42 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/22 18:30:43 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exec_cmd(t_exec_cmd *exec_cmd)
{
	ft_bzero(exec_cmd, sizeof (*exec_cmd));
	exec_cmd->infile = STDIN_FILENO;
	exec_cmd->outfile = STDOUT_FILENO;
}

void	free_exe_cmd(t_exec_cmd *exec_cmd)
{
	free(exec_cmd->path);
	free_split(exec_cmd->argv);
	if (exec_cmd->infile != INVALID_FD)
	{
		close(exec_cmd->infile);
	}
	if (exec_cmd->outfile != INVALID_FD)
	{
		close(exec_cmd->outfile);
	}	
}

void	launch_cmd2(t_command *cmd, t_env *env, t_node **root)
{
	t_exec_cmd	exec_cmd;

	init_exec_cmd(&exec_cmd);
	if (open_cmd_files(cmd->redirect_token, &exec_cmd) == FAILURE)
	{
		env->exit_status = FAILURE;
		end_process(root, env);
	}
	if (cmd->token->word == NULL)
	{
		env->exit_status = SUCCESS;
		end_process(root, env);
	}
	exec_cmd.argv = get_cmd_argv(cmd);
	if (exec_cmd.argv == NULL)
	{
		env->exit_status = FAILURE;
		free_exe_cmd(&exec_cmd);
		end_process(root, env);
	}
	exec_cmd.path = get_cmd_path((const char *)exec_cmd.argv[0], (const t_env) * env, &env->exit_status);
	if (exec_cmd.path == NULL)
	{
		end_process(root, env);
	}
	if (access(exec_cmd.path, X_OK) == -1)
	{
		ft_fprintf(2, "minishel: %s :%s\n", exec_cmd.path, strerror(errno));
		env->exit_status = FAILURE;
		end_process(root, env);
	}
	if (exec_cmd.infile != STDIN_FILENO)
	{
		dup2(exec_cmd.infile, STDIN_FILENO);
		close(exec_cmd.infile);
	}
	if (exec_cmd.outfile != STDOUT_FILENO)
	{
		dup2(exec_cmd.outfile, STDOUT_FILENO);
		close(exec_cmd.outfile);
	}
	execve(exec_cmd.path, exec_cmd.argv, env->variables);
}

int	test_fork(t_command *cmd, t_env *env, t_node **root)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		launch_cmd2(cmd, env, root);
	}
	else
	{
		waitpid(pid, &env->exit_status, 0);
		if (WIFEXITED(env->exit_status))
				env->exit_status = WEXITSTATUS(env->exit_status);
	}
	return (env->exit_status);
}

int	launch_cmd(t_exec_cmd **exec_cmd, t_command **cmd, t_env *env, t_node *root)
{
	(void)exec_cmd;
	(void)cmd;
	(void)env;
	(void)root;
	return (SUCCESS);
}