/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:24:25 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/03/04 11:24:26 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_str_digit(const char *str)
{
	int	char_num;

	char_num = 0;
	while (str[char_num] != '\0')
	{
		if (ft_isdigit(str[char_num] == FALSE))
		{
			return (FALSE);
		}
		++char_num;
	}
	return (TRUE);
}

static char	*get_shlvl_str(void)
{
	int		shlvl;
	char	*shlvl_str;
	char	*shlvl_full_str;

	shlvl = ft_atoi(getenv("SHLVL"));
	shlvl += 1;
	shlvl_str = ft_itoa(shlvl);
	if (shlvl_str == NULL)
	{
		ft_fprintf(2, "minishell: %s\n", strerror(errno));
		return (NULL);
	}
	shlvl_full_str = ft_strjoin("SHLVL=", shlvl_str);
	free(shlvl_str);
	if ((shlvl_full_str) == NULL)
	{
		ft_fprintf(2, "minishell: %s\n", strerror(errno));
	}
	return (shlvl_full_str);
}

void	update_shlvl(t_env env)
{
	char	*shlvl_str;
	char	**line_address;

	if (is_str_digit(getenv("SHLVL")) == FALSE)
	{
		return ;
	}
	shlvl_str = get_shlvl_str();
	if (shlvl_str == NULL)
	{
		return ;
	}
	line_address = get_line_address("SHLVL", (const t_env) env);
	free(*line_address);
	*line_address = shlvl_str;
}
