/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:30:55 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/25 12:32:58 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "get_next_line.h"
#include "libft.h"
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

char	*trim_limit_dup(t_token *here_doc, unsigned int *len_limiter)
{
	unsigned int	i;
	unsigned int	len_to_cpy;
	char			*limiter;
	char			quotes;

	limiter = malloc(sizeof(*limiter) * here_doc->len_word + 2);
	if (limiter == NULL)
		return (NULL);
	i = 0;
	while (here_doc->word[i])
	{
		len_to_cpy = go_to_next_quotes(&here_doc->word[i], '\0');
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

static char	*get_limiter(t_token *here_doc)
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

void	get_stdin(t_token *here_doc, char *limiter, unsigned int len_lim)
{
	unsigned int	i;
	char			*line;

	here_doc->len_word = 0;
	i = 0;
	while (1)
	{
		ft_printf("here_doc> ");
		line = get_next_line(0);
		if (line == NULL)
		{
			ft_fprintf(2, "minishell: warning: here_document, delimited by end-of-file wanted: %s", limiter);
			break ;
		}
		if (ft_strncmp(limiter, line, len_lim + 1) == 0)
			break ;
		here_doc->word = ft_strjoin_free_s1(here_doc->word, line, &here_doc->len_word);
		if (here_doc->word == NULL)
		{
			here_doc->type = ERROR;
			return ;
		}
		free(line);
	}
	free(line);
}

int	is_here_doc(const int previous_type, const int current_type)
{
	if (previous_type == HERE_DOC && current_type == WORD)
		return (TRUE);
	return (FALSE);
}

void	here_doc_handle_list(t_token *here_doc, t_token **head)
{
	t_token	*redirect;

	redirect = here_doc->previous;
	here_doc->type = redirect->type;
	if (redirect->previous == NULL)
	{
		(*head) = here_doc;
		ft_del_token(redirect);
		here_doc->previous = NULL;
	}
	else
	{
		redirect->previous->next = here_doc;
		here_doc->previous = redirect->previous;
		ft_del_token(redirect);
	}
;
}

void	do_here_doc(t_token *here_doc, t_token **head)
{
	char 	*limiter;

	if (head == NULL || *head == NULL || here_doc->word == NULL)
		return ;
	here_doc_handle_list(here_doc, head);
	limiter = get_limiter(here_doc);
	if (limiter == NULL)
		return ;
	get_stdin(here_doc, limiter, here_doc->len_word);
	free(limiter);
}
