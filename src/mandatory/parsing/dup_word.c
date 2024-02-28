/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:42:47 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/28 19:43:51 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_dup_word(
		const char *buf, const unsigned int len_buf, t_token *token)
{
	unsigned int	i;
	unsigned int	j;
	char			*word;
	char			quotes;

	i = 0;
	j = 0;
	quotes = '\0';
	word = malloc(sizeof(*word) * (len_buf + 1));
	if (!word)
		return (NULL);
	while (i < len_buf)
	{
		word[j] = buf[i];
		i++;
		j++;
	}
	word[j] = '\0';
	token->len_word = j;
	if (quotes != '\0')
		token->type = ERROR;
	return (word);
}
