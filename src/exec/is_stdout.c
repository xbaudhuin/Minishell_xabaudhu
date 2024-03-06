/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_stdout.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:57:05 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/03/05 13:57:05 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ino_cmp(ino_t ino_stdout, ino_t ino_fd1, const char *path)
{
	struct stat	buffer;
	int			status;

	status = lstat(path, &buffer);
	if (status == -1)
	{
		ft_fprintf(2, "minishell: is_stdout: %s", strerror(errno));
		return (FALSE);
	}
	if (buffer.st_ino == ino_stdout || buffer.st_ino == ino_fd1)
	{
		return (TRUE);
	}
	else
	{
		return (FALSE);
	}		
}

int	is_stdout(const char *path)
{
	ino_t		ino_stdout;
	ino_t		ino_fd1;
	struct stat	buffer;
	int			status;

	status = lstat("/dev/stdout", &buffer);
	if (status == -1)
	{
		ft_fprintf(2, "minishell: is_stdout: %s", strerror(errno));
		return (FALSE);
	}
	ino_stdout = buffer.st_ino;
	status = lstat("/proc/self/fd/1", &buffer);
	if (status == -1)
	{
		ft_fprintf(2, "minishell: is_stdout: %s", strerror(errno));
		return (FALSE);
	}
	ino_fd1 = buffer.st_ino;
	return (ino_cmp(ino_stdout, ino_fd1, path));
}
