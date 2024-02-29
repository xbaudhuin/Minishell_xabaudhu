/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:55:54 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/02/29 11:55:56 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"






void	ft_readline(void)
{
	char	*buf;
	t_token	*head;
	t_node	*root;
	int		error;

	error = 0;
	head = NULL;
	root = NULL;
	while (1)
	{
		buf =  readline("minishell> ");
		if (!buf)
			return ;
		if (ft_strlen(buf) > 0)
		{
			add_history(buf);
		}
		if (ft_strncmp(buf, "exit", 5) == 0)
		{
			free(buf);
			break ;
		}
		parse_to_token(buf, &head);
		if (head != NULL && check_token_list(&head) == TRUE)
		{
			print_token(&head);
			create_tree(&head, &root, &error);
			print_tree(&root, 0);
		}
		free_tree(&root);
		head = NULL;
		root = NULL;
		free(buf);
	}
	rl_clear_history();
}
/*
void	ft_readline2(int ac, char **av)
{
	t_token	*head;
	t_node	*root;
	int		error;
	int i = 1;

	error = 0;
	head = NULL;
	while (i < ac)
	{
		if (ft_strncmp(av[i], "exit", 5) == 0)
		{
			break ;
		}
		parse_to_token(av[i], &head);
		if (head != NULL && check_token_list(&head) == TRUE)
		{
			print_token(&head);
			create_tree(&head, &root, &error);
			print_tree(&root, 0);
		}
		free_tree(&root);
		if (head != NULL)
		ft_del_
		head = NULL;
		root = NULL;
		i++;
	}
}
*//*

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	ft_readline();
	return (0);
}*/
