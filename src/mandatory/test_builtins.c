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
	char	*line;
	char	**argv_cmd;
	int		buildin_type;
	
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (ft_strlen(line) > 0)
			add_history((const char *)line);
		argv_cmd = ft_split(line, ' ');
		if (argv_cmd == NULL)
		{
			free(line);
			break ;
		}
		free(line);
		buildin_type = is_builtin((const char **)argv_cmd);
		my_env->exit_status = launch_cmd((const char **)argv_cmd, my_env, buildin_type);
		free_split(argv_cmd);
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **main_env)
{
	t_env	my_env;
	char	*test[] = {"/bin/sleep", "5" ,NULL};

	(void)ac;
	(void)av;
	handle_sigquit(TRUE);
	handle_sigint(TRUE);
	printf("I m gonna sleep 5 seconds\n");
	if (fork() == 0)
	{
		handle_sigint(FALSE);
		handle_sigquit(FALSE);
		execve("/bin/sleep", test, main_env);
	}
	wait(NULL);
	printf("test wait\n");
	my_env = create_env((const char **)main_env);
	if (my_env.variables == NULL || ft_getenv("PWD", (const t_env) my_env) == NULL)
	{
		return (MALLOC_FAIL);
	}
	read_cmd_line(&my_env);
	builtin_exit(&my_env);
}
