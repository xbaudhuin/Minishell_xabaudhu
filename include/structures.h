/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoyen-- <ldoyen--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:26:14 by ldoyen--          #+#    #+#             */
/*   Updated: 2024/02/28 21:07:40 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdio.h>

typedef struct s_env
{
	char	**variables;
	size_t	allocated_size;
	int		pwd_unset_time;
	int		was_oldpwd_unset;
	int		exit_status;
}			t_env;

typedef struct s_token
{
	int				type;
	char			*word;
	unsigned int	len_word;
	unsigned int	depths;
	struct s_token	*previous;
	struct s_token	*next;
}			t_token;

typedef struct s_command
{
	t_token	*token;
	t_token	*redirect_token;
}			t_command;

typedef struct s_exec_cmd
{
	char	**argv;
	char	*path;
	int		infile;
	int		outfile;
}			t_exec_cmd;

typedef struct s_node
{
	t_command		**cmd;
	int				exit_status;
	int				type;
	struct s_node	*left_node;
	struct s_node	*right_node;
	struct s_node	*parent_node;
}			t_node;

typedef int(*t_is_valid_type)(int);

#endif
