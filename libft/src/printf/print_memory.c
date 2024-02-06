/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:24:46 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/17 22:05:23 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_len_address(void *ptr)
{
	uintptr_t	add;
	int			len;

	add = (uintptr_t)ptr;
	len = 0;
	if (!ptr)
		return (5);
	while (add)
	{
		add /= 16;
		len++;
	}
	return (len + 2);
}

int	address_to_str(void *ptr, char *str, int len)
{
	int			i;
	uintptr_t	add;
	const char	base_memory[16] = "0123456789abcdef";

	add = (uintptr_t)ptr;
	i = len - 1;
	if (!ptr)
	{
		ft_memmove_size(str, "(nil)", 5);
		return (5);
	}
	str[0] = '0';
	str[1] = 'x';
	while (add)
	{
		str[i] = base_memory[add % 16];
		add /= 16;
		i--;
	}
	while (i > 1)
	{
		str[i] = '0';
		i--;
	}
	return (len);
}

void	fill_memory(char *ret, t_flags *flag, void *ptr, int len)
{
	int	i;

	i = 0;
	if (flag->padding && !flag->minus)
		i += ft_memset_size(ret, ' ', flag->padding);
	i += address_to_str(ptr, &ret[i], len);
	if (flag->padding && flag->minus)
		i += ft_memset_size(&ret[i], ' ', flag->padding);
	ret[flag->width] = '\0';
}

int	print_memory(void *ptr, t_flags *flag)
{
	int		len;
	char	*ret;

	len = get_len_address(ptr);
	if (flag->width < len)
		flag->width = len;
	else
		flag->padding = flag->width - len;
	ret = malloc(sizeof(*ret) * (flag->width + 1));
	if (!ret)
		return (-1);
	fill_memory(ret, flag, ptr, len);
	flag->width = write(flag->fd, ret, flag->width);
	free(ret);
	return (flag->width);
}
