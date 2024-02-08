/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:16:54 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/02/06 20:00:15 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void printin(t_lexer *lex)
{
	t_lexer *lexi;

	lexi = lex;
	printf("------printin---------\n");
	while (lexi)
	{
		printf("str: %s\n", lexi->str);
		printf("token: %d\n", lexi->token);
		printf("i: %d\n", lexi->i);
		lexi = lexi->next;
	}
	printf("------printin---------\n");
}

int			g_last_ret_code = 0;

static void	minishell_loop(t_tool *shell)
{
	char	*tmp;
	while (1)
	{
        signal_handler();
		tmp = readline("minishell> ");
        signal_handler_idle();
		if (!tmp || !tmp[0])
			msh_exit(NULL, shell);
		shell->arg = ft_strtrim(tmp, " ");
		free(tmp);
		add_history(shell->arg);
		shell->lexer = lexer(shell->arg, shell->lexer, shell);
		if (shell->lexer)
		{
            if (has_heredoc(shell->lexer) == true)
                heredoc(shell);
			// printin(shell->lexer);
           lexer_redux(shell->lexer);
            // printin(shell->lexer);
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
	shell = (t_tool){NULL, NULL, NULL, NULL, 0};
	if (ac != 1 || av[1])
	{
		ft_err("no args accepted", NULL, NULL, 1);
		exit(EXIT_FAILURE);
	}
	shell.reset = 0;
	shell.env = init_env(envp);
	minishell_loop(&shell);
	return (0);
}
