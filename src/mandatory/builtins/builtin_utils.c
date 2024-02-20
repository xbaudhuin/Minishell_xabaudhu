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

#include "minishell.h"

void	print_space(void)
{
	ft_putchar_fd(' ', STDOUT_FILENO);
}

void	print_new_line(void)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int	is_underscore(const char c)
{
	if (c == '_')
	{
		return (TRUE);
	}
	else
	{
		return (FALSE);
	}
}

int	is_equal_exists(const char *arg)
{
	size_t	char_num;

	char_num = 0;
	while (arg[char_num] != '\0')
	{
		if (arg[char_num] == '=')
		{
			return (TRUE);
		}
		++char_num;
	}
	return (FALSE);
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
