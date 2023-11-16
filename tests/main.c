/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:34:02 by vgoncalv          #+#    #+#             */
/*   Updated: 2023/11/11 19:41:36 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//These environment variables arent considered command-line 
//arguments and are typically provided by the shell 
//or the operating system when the program is executed
int	main(int argc, char **argv, char **env)
{
	t_tool	tool;

	if (argc != 1 || argv[1])
	{
		printf("The program does not accept arguments.\n");
		return (1);
	}
	tool.env = ft_arrdup(env);
	init_tool(&tool);
	minishell_loop(&tool);
	return (0);
}
