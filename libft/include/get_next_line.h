/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:55:33 by xabaudhu          #+#    #+#             */
/*   Updated: 2023/12/08 23:40:24 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

typedef struct s_buffer
{
	char	buffer[BUFFER_SIZE + 1];
	size_t	i;
}				t_buffer;

char	*ft_strjoin_chr_free_s1(char *s1, char *s2, size_t *len, size_t *index);
char	*ft_strdup_chr(char *s, size_t *len, size_t *index);
int		check_error(int fd);
char	*get_next_line(int fd);
char	*ft_memcpy_ret(char *dest, char *src, size_t n);

#endif
