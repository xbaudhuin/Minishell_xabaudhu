/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:53:30 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/13 16:53:31 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_space(void)
{
	ft_putchar_fd(' ', 1);
}

void	print_new_line(void)
{
	ft_putchar_fd('\n', 1);
}

int	count_args(const char **argv)
{
	int	nb_args;

	nb_args = 0;
	while (argv[nb_args])
	{
		++nb_args;
	}
	return (nb_args);
}
