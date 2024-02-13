/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:10:44 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/13 18:22:42 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
//# include <stropts.h>
//# include <termcap.h>

# define SUCCESS 0
# define FAILURE 1

# define FALSE 0
# define TRUE 1

typedef struct s_command
{
	char	**args;
	int		fd[2];
}			t_command;

typedef struct s_command_node
{
	t_command				*command;
	int						nb_command;
	int						fork;
	struct s_command_node	*left_node;
	struct s_command_node	*right_node;
	struct s_command_node	*parent_node;
}			t_command_node;

#endif
