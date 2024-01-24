/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:16:54 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/24 18:14:16 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			g_last_ret_code = 0;

static void	minishell_loop(t_tool *shell)
{
	t_lexer	*lex;

	shell->arg = readline("minishell> ");
	shell->arg = ft_strtrim(shell->arg, " ");
	if (!shell->arg || !*shell->arg)
	{
		clean_data(shell);
		del_env(shell->env);
		free(shell->arg);
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	add_history(shell->arg);
	shell->lexer = lexer(shell->arg, shell->lexer);
	lex = shell->lexer;
	while (lex)
	{
		printf("lexer: %i, %s, %i\n", lex->i, lex->str, lex->token);
		lex = lex->next;
	}
	shell->lexer = expander2(shell->env, shell->lexer);
	lex = shell->lexer;
	while (lex)
	{
		printf("lexer expander: %i, %s, %i\n", lex->i, lex->str, lex->token);
		lex = lex->next;
	}
	// shell-> = parser(shell->lexer);
	lst_clear(&shell->lexer);
	// free(shell->tree);
	// minishell_loop(shell);
	del_env(shell->env);
}

int	main(int ac, char **av, char **envp)
{
	t_tool	shell;

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
