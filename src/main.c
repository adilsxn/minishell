/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:16:54 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/25 07:51:22 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			g_last_ret_code = 0;

static void	minishell_loop(t_tool *shell)
{
	while (1)
	{
		sig_handl();
		shell->arg = readline("minishell> ");
		if (shell->arg == NULL)
			msh_exit(NULL, shell);
		shell->arg = ft_strtrim(shell->arg, " ");
		add_history(shell->arg);
		shell->lexer = lexer(shell->arg, shell->lexer);
		shell->lexer = expander2(shell->env, shell->lexer);
		if (has_heredoc(shell->lexer) == true)
			heredoc(shell->lexer);
		shell->lexer = expander2(shell->env, shell->lexer);
		shell->pipes = parser(shell);
		if (shell->pipes != NULL)
			exec_pipe(shell);
		else
			exec_cmd(shell);
		clean_data(shell, false);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_tool	shell;

	ft_bzero(&shell, sizeof(t_tool));
	shell = (t_tool){NULL, NULL, NULL, NULL, NULL};
	shell.envp = ft_arrdup(envp);
	if (ac != 1 || av[1])
	{
		ft_err("no args accepted", NULL);
		exit(EXIT_FAILURE);
	}
	init_env(envp, &shell.env);
	minishell_loop(&shell);
	return (0);
}
