/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:16:54 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/02/12 21:57:24 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	printin(t_lexer *lex)
{
	t_lexer	*lexi;

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

static bool	parse_input(t_tool *shell)
{
	char	*tmp;

	signal_handler();
	tmp = readline("minishell> ");
	if (!tmp)
		msh_exit(NULL, shell);
	else if (ft_strequ(tmp, "\0") == 1)
		return (false);
	shell->arg = ft_strtrim(tmp, " ");
	free(tmp);
	add_history(shell->arg);
	shell->lexer = lexer(shell->arg, shell->lexer, shell);
	if (shell->lexer)
	{
		lexer_redux(&shell->lexer);
		shell->lexer = expander2(shell->env, shell->lexer);
		quote_help(shell->lexer);
		if (has_pipe(shell->lexer) == 1)
			shell->pipes = parser(shell);
		else
			return (exec_cmd(shell), false);
	}
	return (true);
}

static void	minishell_loop(t_tool *shell)
{
	while (1)
	{
		if (parse_input(shell) == true)
			exec_pipe(shell);
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
		ft_err("no args accepted", NULL, NULL, 1);
		exit(EXIT_FAILURE);
	}
	shell.reset = 0;
	shell.env = init_env(envp);
	minishell_loop(&shell);
	return (0);
}
