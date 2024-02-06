/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:22:42 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/17 22:07:11 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_flags(t_flags *flag)
{
	flag->hash = 0;
	flag->zero = 0;
	flag->minus = 0;
	flag->width = 0;
	flag->precision = -1;
	flag->space = 0;
	flag->plus = 0;
	flag->padding = 0;
	flag->fd = 1;
}

int	is_end_flag(char c)
{
	if (c == '%')
		return (1);
	else if (c == 'd' || c == 'i')
		return (1);
	else if (c == 'u')
		return (1);
	else if (c == 'x' || c == 'X')
		return (1);
	else if (c == 'c')
		return (1);
	else if (c == 's')
		return (1);
	else if (c == 'p')
		return (1);
	else
		return (0);
}

int	is_early_flags(const char c, t_flags *flag)
{
	if (c == '#' || c == ' ' || c == '+' || c == '0' || c == '-')
	{
		if (c == '#')
			flag->hash = 2;
		if (c == ' ')
			flag->space = 1;
		if (c == '+')
			flag->plus = 1;
		if (c == '0')
			flag->zero = 1;
		if (c == '-')
			flag->minus = 1;
		return (1);
	}
	else
		return (0);
}

int	atoi_flag(const char *format, int *index)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (ft_isdigit(format[i]))
	{
		res = 10 * res + format[i] - '0';
		i++;
	}
	*index += i;
	return (res);
}

int	parse_flags(t_flags *flag, const char *format)
{
	int	i;

	i = 0;
	if (!format)
		return (-1);
	init_flags(flag);
	while (format[i] && is_early_flags(format[i], flag))
		i++;
	if (ft_isdigit(format[i]))
		flag->width = atoi_flag(&format[i], &i);
	if (format[i] == '.')
		flag->precision = atoi_flag(&format[++i], &i);
	if (is_end_flag(format[i]))
		return (i);
	return (-1);
}
