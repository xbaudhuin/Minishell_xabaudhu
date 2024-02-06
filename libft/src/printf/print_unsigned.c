/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:26:39 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/17 22:04:46 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_unsigned_number(unsigned int nb, int len, char *str)
{
	int	i;

	if (!len)
		return (0);
	if (nb == 0)
		str[0] = '0';
	i = len - 1;
	while (nb)
	{
		str[i] = nb % 10 + 48;
		nb /= 10;
		i--;
	}
	return (len);
}

void	fill_unsigned(char *ret, t_flags *flag, unsigned int nb, int len)
{
	int	i;

	i = 0;
	if (flag->padding && !flag->minus && flag->zero <= 0)
		i += ft_memset_size(ret, ' ', flag->padding);
	if (flag->padding && flag->zero > 0)
		i += ft_memset_size(&ret[i], '0', flag->padding);
	if (flag->precision)
		i += ft_memset_size(&ret[i], '0', flag->precision);
	i += get_unsigned_number(nb, len, &ret[i]);
	if (flag->padding && flag->minus)
		i += ft_memset_size(&ret[i], ' ', flag->padding);
	ret[flag->width] = '\0';
}

int	fix_flag_unsigned(unsigned int nb, t_flags *flag, int radix)
{
	int	len;
	int	len_max;

	if (flag->zero && flag->precision != -1)
		flag->zero = 0;
	len = get_len_unsigned(nb, radix);
	if (nb == 0 && flag->precision == 0)
		len = 0;
	if (flag->precision < len)
		flag->precision = 0;
	else
		flag->precision -= len;
	if (flag->hash && nb == 0)
		flag->hash = 0;
	len_max = len + flag->precision + flag->hash;
	if (flag->width < len_max)
		flag->width = len_max;
	else
		flag->padding = flag->width - len_max;
	return (len);
}

int	print_unsigned(unsigned int nb, t_flags *flag)
{
	int		len;
	char	*ret;

	if (flag->hash || flag->plus || flag->space || (flag->zero && flag->minus))
		return (-1);
	len = fix_flag_unsigned(nb, flag, 10);
	ret = malloc(sizeof(*ret) * (flag->width + 1));
	if (!ret)
		return (-1);
	fill_unsigned(ret, flag, nb, len);
	flag->width = write(flag->fd, ret, flag->width);
	free(ret);
	return (flag->width);
}
