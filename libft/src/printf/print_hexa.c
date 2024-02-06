/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:35:56 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/17 22:05:01 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_len_unsigned(unsigned int nb, int radix)
{
	int	len;

	len = 0;
	if (nb == 0)
		len++;
	while (nb)
	{
		nb /= radix;
		len++;
	}
	return (len);
}

int	hexa_to_str(unsigned int nb, int len, char *str, char *base)
{
	int	i;

	i = len - 1;
	if (!len)
		return (0);
	if (nb == 0)
		str[0] = '0';
	while (nb)
	{
		str[i] = base[nb % 16];
		nb /= 16;
		i--;
	}
	return (len);
}

char	*fill_hexa(char *base, t_flags *flag, unsigned int nb, int len)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(*ret) * (flag->width + 1));
	if (!ret)
		return (NULL);
	if (flag->padding && !flag->minus && !flag->zero)
		i += ft_memset_size(ret, ' ', flag->padding);
	if (flag->hash)
	{
		ret[i++] = '0';
		ret[i++] = base[10] + 23;
	}
	if (flag->padding && flag->zero)
		i += ft_memset_size(&ret[i], '0', flag->padding);
	if (flag->precision)
		i += ft_memset_size(&ret[i], '0', flag->precision);
	i += hexa_to_str(nb, len, &ret[i], base);
	if (flag->padding && flag->minus)
		i += ft_memset_size(&ret[i], ' ', flag->padding);
	ret[flag->width] = '\0';
	return (ret);
}

int	print_hexa(unsigned int nb, t_flags *flag, char *base)
{
	int		len;
	char	*ret;

	len = fix_flag_unsigned(nb, flag, 16);
	ret = fill_hexa(base, flag, nb, len);
	if (!ret)
		return (-1);
	flag->width = write(flag->fd, ret, flag->width);
	free(ret);
	return (flag->width);
}
