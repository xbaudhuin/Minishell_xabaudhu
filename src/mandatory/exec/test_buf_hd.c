/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_buf_hd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:57:01 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/23 12:57:03 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	struct stat	buf_stat;
	char	*buf = "Test du here_doc.\nCeci est une deuxieme ligne.\n";

	(void)ac;
	(void)env;
	(void)av;
	pipe(pipe_fd);
	write(pipe_fd[1], buf, strlen(buf));
	close (pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	execve(av[1], av + 1, env);
	return (strlen(buf));
}
