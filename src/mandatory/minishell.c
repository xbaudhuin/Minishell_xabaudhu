/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:39:17 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/06 17:44:44 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "printf.h"
#include "get_next_line.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int ac, char **av, char **env)
{
	
	//init_minishell
	//start_read_line
	//in readline, parse each line:
	//				-separate each command
	//				-analyze and expand each command (!* launch the command for each correspong file)
	//				-transform analyzed command into cmd_table
	//				-exec all the command
	//				-wait next command
	readline("minishell> ");


}
