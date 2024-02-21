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

int	launch_cmd(const char **argv, t_env *my_env, int last_exit, int buildin_type)
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
	else if (strncmp(argv[0], "$?", ft_strlen("$?")) == SUCCESS)
		return (printf("Last exit = %d\n", last_exit), SUCCESS);
	else if (buildin_type == ECHO)
		return (echo(argv));
	else
		return (SUCCESS);

}

int	main(int ac, char **av, char **main_env)
{
	char	**argv_cmd;
	char	*line;
	t_env	my_env;
	int		last_exit;
	int		buildin_type;

	(void)ac;
	(void)av;
	last_exit = SUCCESS;
	my_env = create_env((const char **)main_env);
	if (my_env.variables == NULL || ft_getenv("PWD", (const t_env) my_env) == NULL)
	{
		return (MALLOC_FAIL);
	}
	while (1)
	{
		ft_printf("minishell> ");
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			break ;
		}
		if (ft_strlen(line) > 1)
			line[ft_strlen(line) - 1] = '\0';
		argv_cmd = ft_split(line, ' ');
		if (argv_cmd == NULL)
		{
			free(line);
			break ;
		}
		free(line);
		buildin_type = is_builtin((const char **)argv_cmd);
		last_exit = launch_cmd((const char **)argv_cmd, &my_env, last_exit, buildin_type);
		free_split(argv_cmd);
	}
	free_env(my_env);
}
