/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:31:20 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/17 22:04:11 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_type(va_list args, const char *format, t_flags *flag)
{
	int	j;
	int	i;

	j = -1;
	i = 0;
	if (format[i] == '%')
		j = print_percent(flag->fd);
	if (format[i] == 'd' || format[i] == 'i')
		j = print_signed(va_arg(args, int), flag);
	if (format[i] == 'u')
		j = print_unsigned(va_arg(args, unsigned int), flag);
	if (format[i] == 'x')
		j = print_hexa(va_arg(args, unsigned int), flag, "0123456789abcdef");
	if (format[i] == 'X')
		j = print_hexa(va_arg(args, unsigned int), flag, "0123456789ABCDEF");
	if (format[i] == 'c')
		j = print_char(va_arg(args, int), flag);
	if (format[i] == 's')
		j = print_string(va_arg(args, char *), flag);
	if (format[i] == 'p')
		j = print_memory(va_arg(args, void *), flag);
	return (j);
}

int	print_args(va_list args, const char *format, long int *to_print)
{
	t_flags	flag;
	int		i;
	int		j;

	i = parse_flags(&flag, format);
	if (i == -1)
		return (-1);
	j = check_type(args, &format[i], &flag);
	if (j == -1)
		return (-1);
	*to_print += j;
	return (i + 2);
}

int	parse_format(const char *format, va_list args)
{
	int			i;
	int			j;
	long int	to_print;

	i = 0;
	to_print = 0;
	while (format[i])
	{
		j = 0;
		i += print_format(&format[i], &to_print);
		if (format[i] == '%')
			j = print_args(args, &format[i + 1], &to_print);
		if (j == -1 || to_print > 2147483647)
			return (-1);
		i += j;
	}
	return (to_print);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	long int	to_print;

	if (!format || !format[0])
		return (0);
	va_start(args, format);
	to_print = parse_format(format, args);
	va_end(args);
	return ((int)to_print);
}
