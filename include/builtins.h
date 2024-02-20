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

void	print_space(void);
void	print_new_line(void);
int		is_underscore(const char c);
int		is_equal_exists(const char *arg);
int		count_args(const char **argv);
int		check_option(const char **argv, const char *builtin);

int		echo(const char **argv);
int		pwd(const char **argv);
int		env(const char **argv, const t_env env);
int		export(const char **argv, t_env *env);
int		unset(const char **argv, t_env *env);

# define WRG_OPT 2
# define MALLOC_FAIL 3


#endif
