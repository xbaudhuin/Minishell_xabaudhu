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

int	launch_cmd(const char **argv, t_env *my_env, int last_exit)
{
	if (strncmp(argv[0], "export", ft_strlen("export")) == SUCCESS)
		return (export(argv, my_env));
	else if (strncmp(argv[0], "env", ft_strlen("env")) == SUCCESS)
		return (env(argv, (const t_env)*my_env));
	else if (strncmp(argv[0], "pwd", ft_strlen("pwd")) == SUCCESS)
		return (pwd(argv));
	else if (strncmp(argv[0], "$?", ft_strlen("$?")) == SUCCESS)
		return (printf("Last exit = %d\n", last_exit), SUCCESS);
	else if (strncmp(argv[0], "echo", ft_strlen("echo")) == SUCCESS)
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

	(void)ac;
	(void)av;
	last_exit = SUCCESS;
	my_env = create_env((const char **)main_env);
	while (1)
	{
		ft_printf("minishell> ");
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			break ;
		}
		argv_cmd = ft_split(line, ' ');
		free(line);
		last_exit = launch_cmd((const char **)argv_cmd, &my_env, last_exit);
		free(argv_cmd);
	}
	free_env(my_env);
}
