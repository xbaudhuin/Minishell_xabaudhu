/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_exit_arg_valid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:26:42 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/03/04 11:26:45 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exit_arg_valid(const char *str)
{
	int	char_num;

	char_num = 1;
	if (ft_isdigit(str[0]) == FALSE && str[0] != '+' && str[0] != '-')
	{
		return (FALSE);
	}
	if (ft_isdigit(str[0]) == FALSE && ft_isdigit(str[1]) == FALSE)
	{
		return (FALSE);
	}
	while (str[char_num] != '\0')
	{
		if (ft_isdigit(str[char_num]) == FALSE)
		{
			return (FALSE);
		}
		++char_num;
	}
	return (TRUE);
}
