/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:34:02 by vgoncalv          #+#    #+#             */
/*   Updated: 2023/12/12 22:13:04 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//These environment variables arent considered command-line 
//arguments and are typically provided by the shell 
//or the operating system when the program is executed
int	main(int argc, char **argv, char **envp)
{
	t_tool	tool;

	if (argc != 1 || argv[1])
	{
		printf("The program does not accept arguments.\n");
		return (1);
	}
	init_tool(&tool);
		return (1);
	tool.env = ft_arrdup(envp);
	minishell_loop(&tool);
	return (0);
}
