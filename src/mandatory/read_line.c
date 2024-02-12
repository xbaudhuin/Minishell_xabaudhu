/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:34:58 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/12 19:15:10 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_printf.h"
#include "string.h"
//read_line rl_clear_history rl_on_new_line
//rl_replace_line rl_redisplay, add_history

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

//character special () && || | $ * "" '' $? >> > << < 'espace outside quotes'
// dollar seul = '$'

void	early_parse(char *buf)
{

}

void	ft_readline(void)
{
	char	*buf;

	while (1)
	{
		buf =  readline("minishell> ");
		if (!buf)
			return ;
		if (ft_strlen(buf) > 0)
			add_history(buf);
		early_parse(buf);
		free(buf);
	}
	rl_clear_history();
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	ft_readline();
	return (0);
}

