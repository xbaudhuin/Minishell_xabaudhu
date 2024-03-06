/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:06:02 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/20 17:06:03 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option(const char **argv, const char *builtin)
{
	if (count_args(argv) > 1 && ft_strlen(argv[1]) > 1 && argv[1][0] == '-')
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: -%c: invalid option\n", builtin, argv[1][1]);
		return (FAILURE);
	}
	else
	{
		return (SUCCESS);
	}
}
