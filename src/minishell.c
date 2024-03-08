/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:39:17 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/23 18:42:54 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_global;

static void	update_exit_status(t_env *env)
{
	if (g_global == SIGINT || g_global == 1)
	{
		env->exit_status = 130;
	}
}

static void	new_line_on_child_sigint(t_env *env)
{
	if (env->exit_status == 130)
	{
		write(1, "\n", 1);
	}
}

static void	interpret_cmd_line(t_env *my_env, char *buf)
{
	t_token	*head;
	t_node	*root;
	int		error;

	error = 0;
	head = NULL;
	root = NULL;
	update_exit_status(my_env);
	if (ft_strlen(buf) > 0)
		add_history(buf);
	g_global = 0;
	parse_to_token(buf, &head);
	free(buf);
	if (head != NULL && check_token_list(&head) == TRUE)
	{
		if (create_tree(&head, &root, &error, NULL) == FAILURE)
			free_tree(go_to_root(root));
		handle_sigint(IGNORE);
		my_env->exit_status = launch_tree(root, my_env);
	}
	new_line_on_child_sigint(my_env);
	free_tree(go_to_root(root));
}

static void	do_readline_loop(t_env *my_env)
{

	char	*buf;
	// t_token	*head;
	// t_node	*root;
	// int		error;

	
	// error = 0;
	while (1)
	{
		// head = NULL;
		// root = NULL;
		handle_sigint(NEW_PROMPT);
		buf =  readline("minishell> ");
		if (!buf)
			return ;
		else
		{
			// head = NULL;
			// root = NULL;
			// update_exit_status(my_env);
			// if (ft_strlen(buf) > 0)
			// 	add_history(buf);
			// g_global = 0;
			// parse_to_token(buf, &head);
			// free(buf);
			// if (head != NULL && check_token_list(&head) == TRUE)
			// {
			// 	if (create_tree(&head, &root, &error, NULL) == FAILURE)
			// 		free_tree(go_to_root(root));
			// 	handle_sigint(IGNORE);
			// 	my_env->exit_status = launch_tree(root, my_env);
			// }
			// if (my_env->exit_status == 130)
			// {
			// 	write(1, "\n", 1);
			// }
			// free_tree(go_to_root(root));
			interpret_cmd_line(my_env, buf);
		}
	}
}

void	minishell(const char **main_env)
{
	t_env	my_env;

	handle_sigquit(TRUE);
	handle_sigint(NEW_PROMPT);
	my_env = create_env(main_env);
	if (my_env.variables == NULL || ft_getenv("PWD", (const t_env)my_env) == NULL
		|| ft_getenv("SHLVL", (const t_env)my_env) == NULL)
	{
		free_env(&my_env);
		exit (MALLOC_FAIL);
	}
	do_readline_loop(&my_env);
	builtin_exit(NULL, &my_env, NULL);
}