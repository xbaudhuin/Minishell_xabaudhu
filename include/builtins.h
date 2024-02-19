/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:50:55 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/13 16:50:56 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void	print_space(void);
void	print_new_line(void);
int		is_underscore(const char c);
int		is_equal_exists(const char *arg);
int		count_args(const char **argv);

int	echo(const char **argv);
int	pwd(const char **argv);
int	env(const char **argv, const t_env env);

# define WRG_OPT 2
# define MALLOC_FAIL 3


#endif
