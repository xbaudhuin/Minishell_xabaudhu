/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:21:56 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/03/03 13:03:13 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	go_to_next_quotes(const char *str, char quotes)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == quotes)
			break ;
		if (quotes == '\0' && is_quotes(str[i]))
			break ;
		i++;
	}
	return (i);
}

char	*ft_strjoin_free_s1(char *s1, const char *s2, unsigned int *len_join)
{
	char			*join;
	unsigned int	len_s2;

	len_s2 = ft_strlen(s2);
	join = ft_calloc(*len_join + len_s2 + 1, sizeof(*join));
	if (join == NULL)
		return (NULL);
	ft_memmove(join, s1, *len_join);
	ft_memmove(&join[*len_join], s2, len_s2);
	free(s1);
	*len_join += len_s2;
	return (join);
}

static char	*trim_limit_dup(t_token *here_doc, unsigned int *len_limiter)
{
	unsigned int	i;
	unsigned int	len_to_cpy;
	char			*limiter;
	char			quotes;

	limiter = malloc(sizeof(*limiter) * here_doc->len_word + 2);
	if (limiter == NULL)
		return (NULL);
	i = 0;
	quotes = '\0';
	while (here_doc->word[i])
	{
		len_to_cpy = go_to_next_quotes(&here_doc->word[i], quotes);
		ft_memmove(&limiter[*len_limiter], &here_doc->word[i], len_to_cpy);
		i += len_to_cpy;
		*len_limiter += len_to_cpy;
		if (is_quotes(here_doc->word[i]))
		{
			quotes = here_doc->word[i];
			i++;
		}
	}
	limiter[*len_limiter] = '\n';
	*len_limiter += 1;
	limiter[*len_limiter] = '\0';
	return (limiter);
}

char	*get_limiter(t_token *here_doc)
{
	char			*limiter;
	unsigned int	len_limiter;

	len_limiter = 0;
	limiter = NULL;
	limiter = trim_limit_dup(here_doc, &len_limiter);
	if (limiter == NULL)
	{
		here_doc->type = ERROR;
		return (NULL);
	}
	free(here_doc->word);
	here_doc->word = NULL;
	here_doc->len_word = len_limiter;
	return (limiter);
}
