/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:39:35 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/29 14:39:35 by ldoyen--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# define OLD 1
# define NEW 2

t_env	create_env(const char **main_env);
void	free_env(t_env *env);
char	*ft_getenv(const char *name, const t_env env);
char	**get_line_address(const char *name, const t_env env);
t_env	get_expended_env(t_env old_env, int *ext_sts);
char	**get_line_address(const char *name, const t_env env);

#endif
