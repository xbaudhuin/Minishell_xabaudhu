/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:31:36 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/28 17:31:22 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_early_wildcard(const char *str, const char *file_name)
{
	unsigned int	len;

	len = ft_strlen(str);
	if (ft_strncmp(str, file_name, len) == 0)
		return ((char *)&file_name[len]);
	return (NULL);
}

static int	check_last_wildcard(const char *str, const char *file_name)
{
	if (str == NULL)
		return (TRUE);
	if (ft_reverse_ncmp(str, file_name, ft_strlen(str)) == 0)
		return (TRUE);
	return (FALSE);
}

int	compare_wildcard(char **split, unsigned int size_split, char *file)
{
	unsigned int	i;

	i = 0;
	if (split[i] != NULL)
	{
		file = check_early_wildcard(split[i], file);
		if (file == NULL)
			return (FALSE);
		i++;
	}
	while (i < size_split - 1)
	{
		if (split[i] == NULL)
			i++;
		else
		{
			file = ft_end_strnstr(file, split[i], ft_strlen(file));
			if (file == NULL)
				return (FALSE);
			i++;
		}
	}
	return (check_last_wildcard(split[size_split - 1], file));
}

char	*ft_strjoin_wildcard(char *s1, const char *s2)
{
	unsigned int	len_s1;
	unsigned int	len_s2;
	char			*join;

	if (s2 == NULL)
		return (s1);
	if (s1 == NULL)
		return (ft_strdup(s2));
	len_s1 = 0;
	if (s1 != NULL)
		len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = ft_calloc(len_s1 + len_s2 + 2, sizeof(*join));
	if (join == NULL)
		return (free(s1), NULL);
	ft_memmove(join, s1, len_s1);
	join[len_s1] = ' ';
	ft_memmove(&join[len_s1 + 1], s2, len_s2);
	join[len_s1 + len_s2 + 1] = '\0';
	free(s1);
	return (join);
}
