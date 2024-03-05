/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_stdin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:39:51 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/03/05 13:39:52 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ino_cmp(ino_t ino_stdin, ino_t ino_fd0, const char *path)
{
	struct stat	buffer;
	int			status;

	status = lstat(path, &buffer);
	if (status == -1)
	{
		ft_fprintf(2, "minishell: is_stdin: %s", strerror(errno));
		return (FALSE);
	}
	if (buffer.st_ino == ino_stdin || buffer.st_ino == ino_fd0)
	{
		return (TRUE);
	}
	else
	{
		return (FALSE);
	}		
}

int	is_stdin(const char *path)
{
	ino_t		ino_stdin;
	ino_t		ino_fd0;
	struct stat	buffer;
	int			status;

	status = lstat("/dev/stdin", &buffer);
	if (status == -1)
	{
		ft_fprintf(2, "minishell: is_stdin: %s", strerror(errno));
		return (FALSE);
	}
	ino_stdin = buffer.st_ino;
	status = lstat("/proc/self/fd/0", &buffer);
	if (status == -1)
	{
		ft_fprintf(2, "minishell: is_stdin: %s", strerror(errno));
		return (FALSE);
	}
	ino_fd0 = buffer.st_ino;
	return (ino_cmp(ino_stdin, ino_fd0, path));
}
