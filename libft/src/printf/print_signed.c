/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_signed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:19:02 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/17 22:04:27 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_len_signed(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	if (n < 0)
	{
		len ++;
		n /= -10;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	get_signed_number(int n, int len, char *str)
{
	int	i;

	i = len - 1;
	if (!len)
		return (0);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[i] = -(n % 10) + 48;
		n /= -10;
		i--;
	}
	while (n > 0)
	{
		str[i] = n % 10 + 48;
		n /= 10;
		i--;
	}
	return (len);
}

void	fill_signed(char *ret, t_flags *flag, int n, int len)
{
	int	i;

	i = 0;
	if (flag->padding && !flag->minus && !flag->zero)
		i += ft_memset_size(ret, ' ', flag->padding);
	if (flag->plus == 1)
		ret[i++] = '+';
	if (flag->plus == 2)
		ret[i++] = '-';
	if (flag->space)
		ret[i++] = ' ';
	if (flag->padding && flag->zero)
		i += ft_memset_size(&ret[i], '0', flag->padding);
	if (flag->precision)
		i += ft_memset_size(&ret[i], '0', flag->precision);
	i += get_signed_number(n, len, &ret[i]);
	if (flag->padding && flag->minus)
		i += ft_memset_size(&ret[i], ' ', flag->padding);
	ret[flag->width] = '\0';
}

int	fix_flag_signed(int n, t_flags *flag)
{
	int	len;
	int	len_max;

	if (flag->zero && flag->precision != -1)
		flag->zero = 0;
	len = get_len_signed(n);
	if (n == 0 && flag->precision == 0)
		len = 0;
	if (flag->precision < len)
		flag->precision = 0;
	else
		flag->precision -= len;
	if (n < 0)
	{
		flag->space = 0;
		flag->plus = 1;
	}
	len_max = len + flag->plus + flag->space + flag->precision;
	if (flag->width < len_max)
		flag->width = len_max;
	else
		flag->padding = flag->width - len_max;
	return (len);
}

int	print_signed(int n, t_flags *flag)
{
	int		len;
	char	*ret;

	if (flag->hash)
		return (-1);
	if ((flag->plus && flag->space) || (flag->zero && flag->minus))
		return (-1);
	len = fix_flag_signed(n, flag);
	ret = malloc(sizeof(*ret) * (flag->width + 1));
	if (!ret)
		return (-1);
	if (n < 0)
		flag->plus = 2;
	fill_signed(ret, flag, n, len);
	flag->width = write(flag->fd, ret, flag->width);
	free(ret);
	return (flag->width);
}
