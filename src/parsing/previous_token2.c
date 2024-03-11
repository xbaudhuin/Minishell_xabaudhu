/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   previous_token2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:12:35 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/11 14:53:23 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	previous_pipe_token(const int type)
{
	if (is_word_token(type) == TRUE)
		return (TRUE);
	if (is_redirect_token(type) == TRUE)
		return (TRUE);
	if (is_here_doc_token(type) == TRUE)
		return (TRUE);
	return (FALSE);
}

int	is_here_doc(const int previous_type, const int current_type)
{
	if (previous_type == HERE_DOC_TOKEN && current_type == WORD)
		return (TRUE);
	return (FALSE);
}
