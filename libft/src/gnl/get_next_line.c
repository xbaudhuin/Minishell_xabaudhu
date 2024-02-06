/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:34:25 by xabaudhu          #+#    #+#             */
/*   Updated: 2023/12/01 17:26:58 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	check_buffer(t_buffer *buffer, char **line, size_t *len, size_t *check)
{
	if (buffer->i && buffer->buffer[buffer->i])
	{
		*line = ft_strdup_chr(&buffer->buffer[buffer->i], len, check);
		if (!*line)
			return (0);
		if (*check != 0)
			buffer->i += *check;
	}
	return (1);
}

int	init_var(char **line, size_t *check, size_t *len, ssize_t *read_return)
{
	*line = NULL;
	*check = 0;
	*len = 0;
	*read_return = 1;
	return (1);
}

int	check_error(int fd)
{
	if (fd < 0 || fd > FD_MAX || BUFFER_SIZE <= 0)
		return (0);
	else
		return (1);
}

char	*get_next_line(int fd)
{
	static t_buffer	buffer;
	ssize_t			read_return;
	char			*line;
	size_t			check;
	size_t			len;

	if (!check_error(fd) || !init_var(&line, &check, &len, &read_return))
		return (NULL);
	if (!check_buffer(&buffer, &line, &len, &check))
		return (NULL);
	while (read_return)
	{
		if (check)
			break ;
		read_return = read(fd, buffer.buffer, BUFFER_SIZE);
		buffer.i = 0;
		if (read_return < 0 || (!read_return && !line))
			return (free(line), NULL);
		buffer.buffer[read_return] = '\0';
		line = ft_strjoin_chr_free_s1(line, buffer.buffer, &len, &check);
		if (!line)
			return (free(line), NULL);
		buffer.i += check;
	}
	return (line);
}
