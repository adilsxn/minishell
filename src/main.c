/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:16:54 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/25 15:34:23 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void printin(t_lexer *lex)
{
	t_lexer *lexi;

	lexi = lex;
	while (lexi)
	{
		printf("str: %s\n", lexi->str);
		printf("token: %d\n", lexi->token);
		printf("i: %d\n", lexi->i);
		lexi = lexi->next;
	}
}

int			g_last_ret_code = 0;

static void	minishell_loop(t_tool *shell, char **envp)
{
	while (1)
	{
		shell->envp = ft_arrdup(envp);
		init_env(shell->envp, &shell->env);
		sig_handl();
		shell->arg = readline("minishell> ");
		if (shell->arg == NULL)
			msh_exit(NULL, shell);
		shell->arg = ft_strtrim(shell->arg, " ");
		add_history(shell->arg);
		shell->lexer = lexer(shell->arg, shell->lexer, shell);
		printin(shell->lexer);
		if (shell->lexer)
		{
			shell->lexer = expander2(shell->env, shell->lexer);
			if (has_heredoc(shell->lexer) == true)
				heredoc(shell->lexer);
			shell->lexer = expander2(shell->env, shell->lexer);
			shell->pipes = parser(shell);
			if (shell->pipes != NULL)
				exec_pipe(shell);
			else
				exec_cmd(shell);
		}
		clean_data(shell, false);
		shell->reset = 1;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_tool	shell;

	ft_bzero(&shell, sizeof(t_tool));
	shell = (t_tool){NULL, NULL, NULL, NULL, 0, NULL};
	if (ac != 1 || av[1])
	{
		ft_err("no args accepted", NULL);
		exit(EXIT_FAILURE);
	}
	shell.reset = 0;
	minishell_loop(&shell, envp);
	return (0);
}


