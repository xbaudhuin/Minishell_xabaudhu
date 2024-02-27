/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:27:46 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/27 19:13:52 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "get_next_line.h"
#include "libft.h"
#include "minishell.h"
#include <asm-generic/errno.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>

char	*ft_end_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	if (ft_strlen(little) > len)
		return (NULL);
	while (big[i] && i < len)
	{
		j = 0;
		while (little[j] == big[i + j] && (i + j) < len)
		{
			j++;
			if (little[j] == '\0')
			{
				if (big[i + j] == '\0')
					return (NULL);
				return ((char *)&big[i]);
			}
		}
		i++;
	}
	return (NULL);
}
/*
int	check_wildcard(char *str, const char *file_name, unsigned int *wildcard)
{
	if (compare_wildcard(file_name, str, *wildcard) != NULL)
	{
		if (ft_strlen(str) == *wildcard)
			return (free(str), TRUE);
	}
}

char	next_not_quote_char(const char *s)
{
	unsigned int	i;
	char			quotes;

	i = 0;
	if (is_quotes(s[i]))
		quotes = s[i];
	while (s[i] && s[i] == quotes)
		i++;
	return (s[i]);
}
*/
unsigned int	dup_chr(const char *s, char *dup, char quotes)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != quotes)
	{
		dup[i] = s[i];
		i++;
	}
	return (i);
}

char	*trim_quotes(const char *s, unsigned int len)
{
	char			*trim_dup;
	unsigned int	i;
	unsigned int	j;
	unsigned int	len_quotes;

	trim_dup = ft_calloc(len, sizeof(*trim_dup) + 1);
	if (trim_dup == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0' && s[i] != '*')
	{
		if (is_quotes(s[i]))
		{
			len_quotes = dup_chr(&s[i + 1], &trim_dup[j], s[i]);
			i += len_quotes + 2;
			j += len_quotes;
		}
		else
		{
			trim_dup[j] = s[i];
			i++;
			j++;
		}
	}
	trim_dup[j] = '\0';
	return (trim_dup);
}

/*
int	is_wildcard_expendable(const char *word)
{
	unsigned int	i;
	char			quotes;

	i = 0;
	quotes = '\0';
	while (word[i])
	{
		if (is_quotes(word[i]))
		{
			quotes = word[i];
			while (word[i] && word[i] != quotes)
				i++;
		}
		if (word[i] == '*')
			return (TRUE);
	}
	return (FALSE);
}
*/
int	get_nb_wildcard(const char *word, char c)
{
	unsigned int	i;
	unsigned int	nb_wildcard;
	char			quotes;

	i = 0;
	nb_wildcard = 0;
	quotes = '\0';
	while (word[i] != '\0')
	{
		if (is_quotes(word[i]))
			i += go_to_next_quotes(&word[i + 1], word[i]) + 1;
		if (word[i] == c)
		{
			nb_wildcard++;
			while (word[i] == c)
				i++;
			if (word[i] != '\0')
				nb_wildcard++;
		}
		else
			i++;
	}
	if (nb_wildcard > 0 && word[0] != '*')
		nb_wildcard++;
	return (nb_wildcard);
}

unsigned int	len_till_next_wildcard(const char *word)
{
	unsigned int	i;
	char			quotes;

	i = 0;
	while (word[i] != '\0')
	{
		if (is_quotes(word[i]))
		{
			quotes = word[i];
			i++;
			while (word[i] != '\0' && word[i] != quotes)
			{
				i++;
			}
			i++;
		}
		else if (word[i] == '*')
			break ;
		else
			i++;
	}
	return (i);
}

void	free_wildcard(char **split, unsigned int k)
{
	unsigned int	i;

	i = 0;
	if (split == NULL)
		return ;
	while (i < k)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**ft_split_wildcard(const char *word, unsigned int nb_wildcard)
{
	char			**split;
	unsigned int	i;
	unsigned int	len_to_wildcard;
	unsigned int	k;

	k = 0;
	i = 0;
	split = ft_calloc(nb_wildcard, sizeof(*split));
	if (split == NULL)
		return (NULL);
	while (word[i] != '\0')
	{
		len_to_wildcard = len_till_next_wildcard(&word[i]);
		if (len_to_wildcard == 0)
		{
			split[k] = NULL;
			k++;
			while (word[i] == '*')
				i++;
		}
		else
		{
			split[k] = trim_quotes(&word[i], len_to_wildcard);
			if (split[k] == NULL)
				return (free_wildcard(split, k), NULL);
			k++;
			i += len_to_wildcard;
		}
	}
	return (split);
}

char	**get_split_wildcard(const char *word, unsigned int nb_wildcard)
{
	char			**split_wildcard;

	split_wildcard = NULL;
	split_wildcard = ft_split_wildcard(word, nb_wildcard);
	if (split_wildcard == NULL)
	{
		return (NULL);
	}
	return (split_wildcard);
}

DIR	*get_open_dir(void)
{
	DIR		*dir;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror(RED"wildcard_getcwd:"RESET);
		return (NULL);
	}
	dir = opendir(pwd);
	free(pwd);
	if (dir == NULL)
		return (NULL);
	return (dir);
}

char	*check_early_wildcard(const char *str, const char *file_name)
{
	unsigned int	len;

	len = ft_strlen(str);
	if (ft_strncmp(str, file_name, len) == 0)
		return ((char *)&file_name[len]);
	return (NULL);
}

int	ft_reverse_ncmp(const char *s1, const char *s2, size_t n)
{
	int	i;
	int	j;


	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	if (n == 0)
		return (0);
	while (i >= 0 && j >= 0 && s1[i] == s2[j])
	{
		n--;
		if (n == 0)
			break ;
		i--;
		j--;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

int	check_last_wildcard(const char *str, const char *file_name)
{
	if (ft_reverse_ncmp(str, file_name, ft_strlen(str)) == 0)
		return (TRUE);
	return (FALSE);
}

int	compare_wildcard(char **split, unsigned int size_split, char *file_name)
{
	unsigned int	i;

	i = 0;
	if (split[i] != NULL)
	{
		file_name = check_early_wildcard(split[i], file_name);
		if (file_name == NULL)
			return (FALSE);
		i++;
	}
	while (i < size_split - 1)
	{
		if (split[i] == NULL)
			i++;
		else
		{
			file_name = ft_end_strnstr(file_name, split[i], ft_strlen(file_name));
			if (file_name == NULL)
				return (FALSE);
			i++;
		}
	}
	if (split[size_split - 1] != NULL)
	{
		if (check_last_wildcard(split[size_split - 1], file_name) == FALSE)
			return (FALSE);
	}
	return (TRUE);
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

char	*wildcard_expansion(char *word, const unsigned int size_split)
{
	DIR				*dir;
	char			*str;
	char			**split_word;
	struct	dirent	*ent;

	dir = get_open_dir();
	str = NULL;
	split_word = get_split_wildcard(word, size_split);
	if (dir == NULL || split_word == NULL)
		return (word);
	ent = readdir(dir);
	while (ent)
	{
		if (compare_wildcard(split_word, size_split, ent->d_name) == TRUE)
		{
			str = ft_strjoin_wildcard(str, ent->d_name);
			if (str == NULL)
				break ;
		}
		ent = readdir(dir);
	}
	closedir(dir);
	free_wildcard(split_word, size_split);
	if (errno)
	{
		free(str);
		perror(RED"wildcard_expansion:"RESET);
		return (free(str), NULL);
	}
	if (str == NULL)
	{
		return (word);
	}
	free(word);
	return (str);
}

char	*wildcard(char *word)
{
	unsigned int nb_wildcard;
	char		*str;

	str = NULL;
	if (word == NULL)
		return (NULL);
	nb_wildcard = get_nb_wildcard(word, '*');
	if (nb_wildcard == 0)
	{
		return ((char *)word);
	}
	str = wildcard_expansion(word, nb_wildcard);
	return (str);
}
#include <strings.h>

int main(int ac, char **av)
{
	(void)ac;
	char *str = NULL;
	str = strdup(av[1]);
	str = wildcard(str);
	if (str == NULL)
	{
		ft_printf(RED"str = NULL\n"RESET);
		return (0);
	}
	ft_printf("%s\n", str);
	free(str);
	return (0);
}
