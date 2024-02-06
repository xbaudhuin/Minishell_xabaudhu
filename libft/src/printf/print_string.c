/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:39:16 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/17 22:03:00 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format(const char *format, long int *to_print)
{
	int	i;

	i = 0;
	while (format[i] && format[i] != '%')
		i++;
	write(1, format, i);
	*to_print += i;
	return (i);
}

void	fill_string(char *str, char *ret, t_flags *flag)
{
	int	i;

	i = 0;
	if (flag->padding && !flag->minus)
		i += ft_memset_size(ret, ' ', flag->padding);
	if (str == NULL)
		i += ft_memmove_size(&ret[i], "(null)", 7);
	else
		i += ft_memmove_size(&ret[i], str, flag->precision);
	if (flag->padding && flag->minus)
		i += ft_memset_size(&ret[i], ' ', flag->padding);
	ret[flag->width] = '\0';
}

int	print_string(char *str, t_flags *flag)
{
	char	*ret;
	int		len;

	if (flag->hash || flag->zero || flag->plus)
		return (-1);
	len = ft_strlen_safe(str);
	if (str == NULL && (flag->precision == -1 || flag->precision >= 6))
		len = 6;
	if ((flag->precision == -1 || flag->precision > len))
		flag->precision = len;
	if (flag->width < flag->precision)
		flag->width = flag->precision;
	flag->padding = flag->width - flag->precision;
	if (flag->padding < 0)
		flag->padding = 0;
	ret = malloc(sizeof(*ret) * (flag->width + 1));
	if (!ret)
		return (-1);
	fill_string(str, ret, flag);
	flag->width = write(flag->fd, ret, flag->width);
	free(ret);
	return (flag->width);
}
