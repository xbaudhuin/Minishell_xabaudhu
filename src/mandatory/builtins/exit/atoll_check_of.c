/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoll_check_of.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:01:55 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/03/05 15:01:55 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	atoll_check_of(const char *str, int *error)
{
	long long	result;
	int			i;
	int			sign;

	*error = SUCCESS;
	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (ft_isdigit(str[i]) == FALSE)
		*error = FAILURE;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + sign * (str[i++] - '0');
		if ((sign == 1 && result < 0) || (sign == -1 && result > 0))
			*error = FAILURE;
	}
	if (str[i] != '\0')
		*error = FAILURE;
	return (result);
}
