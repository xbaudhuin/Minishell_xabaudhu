/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:16:18 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/03/04 12:29:18 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global;

void	read_cmd_line(t_env *my_env)
{

	char	*buf;
	t_token	*head;
	t_node	*root;
	int		error;
	int		new_line;

	
	error = 0;
	head = NULL;
	root = NULL;
	(void)my_env;
	new_line = 0;
	while (1)
	{
		handle_sigint(NEW_PROMPT);
		buf =  readline("minishell> ");
		if (!buf)
			return ;
		else
		{
			if (g_global == SIGINT)
			{
				my_env->exit_status = 130;
			}
			if (ft_strlen(buf) > 0)
				add_history(buf);
			g_global = 0;
			parse_to_token(buf, &head);
			free(buf);
			if (head != NULL && check_token_list(&head) == TRUE)
			{
				if (create_tree(&head, &root, &error, NULL) == FAILURE)
					free_tree(go_to_root(root));
				my_env->exit_status = launch_tree(root, my_env);
			}
			else
				my_env->exit_status = 2;
			if (my_env->exit_status == 130)
			{
				write(1, "\n", 1);
			}
			free_tree(go_to_root(root));
			head = NULL;
			root = NULL;
		}
	}
}

int	main(int ac, char **av, char **main_env)
{
	t_env	my_env;
	


	(void)ac;
	(void)av;
	handle_sigquit(TRUE);
	handle_sigint(NEW_PROMPT);
	my_env = create_env((const char **)main_env);
	if (my_env.variables == NULL || ft_getenv("PWD", (const t_env) my_env) == NULL || ft_getenv("SHLVL", (const t_env) my_env) == NULL)
	{
		return (MALLOC_FAIL);
	}
	read_cmd_line(&my_env);
	builtin_exit(NULL, &my_env, NULL);
}
