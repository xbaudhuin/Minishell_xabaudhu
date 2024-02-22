/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:07:15 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/22 15:09:19 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_sigquit(int ignore)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof (action));
	if (ignore == TRUE)
	{
		action.sa_handler = SIG_IGN;
	}
	else
	{
		action.sa_handler = SIG_DFL;
	}
	sigaction(SIGQUIT, &action, NULL);
	return (SUCCESS);
}
