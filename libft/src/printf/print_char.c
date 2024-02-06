/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:00:58 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/17 22:04:04 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_percent(int fd)
{
	write(fd, "%", 1);
	return (1);
}

int	print_char(int c, t_flags *flag)
{
	char	*str;
	int		i;

	i = 0;
	if (!flag->width)
		flag->width = 1;
	str = malloc(sizeof(*str) * (flag->width + 1));
	if (!str)
		return (-1);
	flag->padding = flag->width - 1;
	if (flag->width > 1 && !flag->minus)
		i += ft_memset_size(str, ' ', flag->padding);
	str[i++] = c;
	if (flag->width > 1 && flag->minus)
		i += ft_memset_size(&str[i], ' ', flag->padding);
	str[flag->width] = '\0';
	flag->width = write(flag->fd, str, flag->width);
	free(str);
	return (flag->width);
}
