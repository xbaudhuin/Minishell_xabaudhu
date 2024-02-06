/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:18:14 by xabaudhu          #+#    #+#             */
/*   Updated: 2023/12/09 00:18:56 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

ssize_t	ft_putstr_fd(char *s, int fd)
{
	if (s && fd)
		return (write(fd, s, ft_strlen(s)));
	return (0);
}
