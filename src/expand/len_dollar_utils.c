/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_dollar_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:49:30 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/08 15:52:55 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	ft_len_unb(unsigned int nb)
{
	unsigned int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

unsigned int	get_len_env(
	char *word, const t_env env, unsigned int len_word)
{
	char			save;
	char			*dollar;
	unsigned int	len_expand;

	save = word[len_word];
	word[len_word] = '\0';
	dollar = ft_getenv(word, env);
	word[len_word] = save;
	if (dollar == NULL)
		return (0);
	len_expand = ft_strlen(dollar);
	return (len_expand);
}
