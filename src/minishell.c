/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:39:17 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/09 14:27:33 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_global;

static void	update_exit_status(t_env *env, const char *buf)
{
	if (g_global == SIGINT || g_global == 1)
	{
		env->exit_status = 130;
	}
	if (ft_strlen(buf) == 0)
	{
		env->exit_status = 0;
	}
}

static void	new_line_on_child_sigint(void)
{
	if ((g_global == SIGINT || g_global == SIGQUIT))
	{
		write(1, "\n", 1);
	}
}

static void	interpret_cmd_line(t_env *my_env, char *buf)
{
	t_token	*head;
	t_node	*root;

	head = NULL;
	root = NULL;
	update_exit_status(my_env, buf);
	if (ft_strlen(buf) > 0)
		add_history(buf);
	g_global = 0;
	parse_to_token(buf, &head, my_env);
	free(buf);
	if (head != NULL && check_token_list(&head, my_env) == TRUE)
	{
		if (create_tree(&head, &root, NULL) == FAILURE)
		{
			free_tree(go_to_root(root));
			root = NULL;
		}
		handle_sigint(IGNORE);
		my_env->exit_status = launch_tree(root, my_env);
		new_line_on_child_sigint();
		if (my_env->exit_status != 130)
			g_global = 0;
	}
	free_tree(go_to_root(root));
}

static void	do_readline_loop(t_env *my_env)
{
	char	*buf;

	while (1)
	{
		handle_sigint(NEW_PROMPT);
		buf = readline("minishell> ");
		if (buf == NULL)
			return ;
		else
		{
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
	if (my_env.variables == NULL
		|| ft_getenv("PWD", (const t_env)my_env) == NULL
		|| ft_getenv("SHLVL", (const t_env)my_env) == NULL)
	{
		free_env(&my_env);
		exit (MALLOC_FAIL);
	}
	do_readline_loop(&my_env);
	builtin_exit(NULL, &my_env, NULL);
}
