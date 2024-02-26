/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:16:18 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/20 12:16:19 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_cmd(const char **argv, t_env *my_env, int buildin_type)
{
	if (buildin_type == EXPORT)
		return (export(argv, my_env));
	else if (buildin_type == ENV)
		return (env(argv, (const t_env)*my_env));
	else if (buildin_type == UNSET)
		return (unset(argv, my_env));
	else if (buildin_type == CD)
		return (cd(argv, my_env));
	else if (buildin_type == PWD)
		return (pwd(argv));
	else if (buildin_type == EXIT)
	{
		free_split((char **)argv);
		builtin_exit(my_env);
	}
	else if (strncmp(argv[0], "$?", ft_strlen("$?")) == SUCCESS)
		return (printf("Last exit = %d\n", my_env->exit_status), SUCCESS);
	else if (buildin_type == ECHO)
		return (echo(argv));
	return (SUCCESS);
}

void	read_cmd_line(t_env *my_env)
{
	// char	*line;
	// char	**argv_cmd;
	// int		buildin_type;
	
	// while (1)
	// {
	// 	line = readline("minishell> ");
	// 	if (!line)
	// 		break ;
	// 	if (ft_strlen(line) > 0)
	// 		add_history((const char *)line);
	// 	argv_cmd = ft_split(line, ' ');
	// 	if (argv_cmd == NULL)
	// 	{
	// 		free(line);
	// 		break ;
	// 	}
	// 	free(line);
	// 	buildin_type = is_builtin((const char **)argv_cmd);
	// 	my_env->exit_status = launch_cmd((const char **)argv_cmd, my_env, buildin_type);
	// 	free_split(argv_cmd);
	// }
	// rl_clear_history();
	char	*buf;
	t_token	*head;
	t_node	*root;
	int		error;

	error = 0;
	head = NULL;
	(void)my_env;
	while (1)
	{
		buf =  readline("minishell> ");
		if (!buf)
			return ;
		if (ft_strlen(buf) > 0)
			add_history(buf);
		if (ft_strncmp(buf, "exit", 5) == 0)
		{
			free(buf);
			break ;
		}
		parse_to_token(buf, &head);
		if (head != NULL && check_token_list(&head) == TRUE)
		{
			//print_token(&head);
			create_tree(&head, &root, &error);
			//print_tree(&root, 0);
		}
		open_cmd_files(root->cmd[0]);
		free_tree(&root);
		head = NULL;
		root = NULL;
		free(buf);
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **main_env)
{
	t_env	my_env;
	//char	*test[] = {"src/cat", "Makefile" ,NULL};

	(void)ac;
	(void)av;
	handle_sigquit(TRUE);
	handle_sigint(TRUE);
	my_env = create_env((const char **)main_env);
	if (my_env.variables == NULL || ft_getenv("PWD", (const t_env) my_env) == NULL)
	{
		return (MALLOC_FAIL);
	}
	char *path = get_cmd_path(av[1], my_env);
	printf("path = %s\n", path);
	if (access(path, X_OK) == -1)
		ft_fprintf(2, "bash: %s: %s\n", path, strerror(errno));
	free(path);
	builtin_exit(&my_env);



	read_cmd_line(&my_env);
	builtin_exit(&my_env);
}
