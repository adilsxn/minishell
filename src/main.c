/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:16:54 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/22 23:15:41 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int g_last_ret_code = 0;

static void  minishell_loop(t_tool *shell)
{
	char *input;
	t_lexer *lexi = NULL;

	input = readline("msh$ ");
	input = ft_strtrim(input, " ");
	if (!input || !*input)
	{
		ft_putendl_fd("exit", 1);
		exit (0);
	}
	add_history(input);
    free(input);
	shell->lexer = lexi;
	//minishell_loop(shell);
}

int main(int ac, char **av, char **envp)
{
	t_tool shell;

    ft_bzero(&shell, sizeof(t_tool));
	if (ac != 1 || av[1])
	{
		ft_err("no args accepted", NULL);
		exit(EXIT_FAILURE);
	}
    sig_handl();
	init_env(envp, &shell.env);
	minishell_loop(&shell);
	return (0);
}
