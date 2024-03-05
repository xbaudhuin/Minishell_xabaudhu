/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:46:10 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/03/05 18:49:02 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_SIGNALS_H
# define MY_SIGNALS_H

enum	e_sigint
{
	NEW_PROMPT = 0,
	CLOSE_IN = 1,
	DEFAULT = 3,
};

int				handle_sigquit(int ignore);
int				handle_sigint(int new_prompt);

#endif
