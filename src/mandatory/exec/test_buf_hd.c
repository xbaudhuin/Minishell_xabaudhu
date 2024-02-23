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
	int make_fd = open("Makefile", O_RDONLY);
	fstat(make_fd, &buf_stat);
	printf("st_size du Makefile en octets = %ld\n", buf_stat.st_size);
	fstat(pipe_fd[0], &buf_stat);
	printf("st_size du pipe_fd en octets = %ld\n", buf_stat.st_size);
	write(pipe_fd[1], buf, strlen(buf));
	close (pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close (make_fd);
	//execve(av[1], av + 1, env);
	return (strlen(buf));
}
