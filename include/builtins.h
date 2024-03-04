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

enum	e_buildin_type
{
	ECHO = 0,
	CD = 1,
	PWD = 2,
	EXPORT = 3,
	UNSET = 4,
	ENV = 5,
	EXIT = 6,
	NONE = 7,
};

# define WRG_OPT 2
# define MALLOC_FAIL 3
# define NB_BUILTIN 7

void	print_space(void);
void	print_new_line(void);
int		is_underscore(const char c);
int		is_equal_exists(const char *arg);
int		count_args(const char **argv);
int		check_option(const char **argv, const char *builtin);
int		is_var_name_valid(const char *arg);
int		is_builtin(const char **argv);
int		is_exit_arg_valid(const char *str);

int		echo(const char **argv);
int		pwd(const char **argv);
int		env(const char **argv, const t_env env);
int		export(const char **argv, t_env *env);
int		unset(const char **argv, t_env *env);
int		cd(const char **argv, t_env *env);
int		builtin_exit(const char **argv, t_env *env, t_data *data);

#endif
