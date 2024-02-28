/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:31:20 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/26 20:12:07 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	fprint_format(int fd, const char *format, long int *to_print)
{
	int	i;

	i = 0;
	while (format[i] && format[i] != '%')
		i++;
	write(fd, format, i);
	*to_print += i;
	return (i);
}

int	fprint_args(int fd, va_list args, const char *format, long int *to_print)
{
	t_flags	flag;
	int		i;
	int		j;

	i = parse_flags(&flag, format);
	flag.fd = fd;
	if (i == -1)
		return (-1);
	j = check_type(args, &format[i], &flag);
	if (j == -1)
		return (-1);
	*to_print += j;
	return (i + 2);
}

int	fparse_format(int fd, const char *format, va_list args)
{
	int			i;
	int			j;
	long int	to_print;

	i = 0;
	to_print = 0;
	while (format[i])
	{
		j = 0;
		i += fprint_format(fd, &format[i], &to_print);
		if (format[i] == '%')
			j = fprint_args(fd, args, &format[i + 1], &to_print);
		if (j == -1 || to_print > 2147483647)
			return (-1);
		i += j;
	}
	return (to_print);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list		args;
	long int	to_print;

	if (!format || !format[0] || fd < 0)
		return (0);
	va_start(args, format);
	to_print = fparse_format(fd, format, args);
	va_end(args);
	return ((int)to_print);
}
