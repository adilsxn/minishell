/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:16:54 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/22 11:07:13 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void  minishell_loop(t_tool *shell)
{
	char *input;
	t_lexer	*lex;

	input = readline("minishell> ");
	input = ft_strtrim(input, " ");
	if (!input || !*input)
	{
		del_env(shell->env);
		free(input);
		ft_putendl_fd("exit", 1);
		exit (0);
	}
	add_history(input);
	shell->lexer = lexer(input, shell->lexer, shell);
	shell->lexer = expander2(shell->env, shell->lexer);
	lex = shell->lexer;
	while (lex)
	{
		if (lex->str)
			printf("lexer: %s\n", lex->str);
		if (lex->token)
			printf("token: %d\n", lex->token);
		lex = lex->next;
	}
	shell->tree = parser(shell->lexer);
	free(shell->lexer);
	tree_exec(shell->tree, shell->env);
	free(shell->tree);
	//minishell_loop(shell);
}

int main(int ac, char **av, char **envp)
{
	t_tool shell;

	shell = (t_tool){NULL, NULL, NULL, NULL};
	if (ac != 1 || av[1])
	{
		printf("No args accepted\n");
		exit(0);
	}
	setup_sgnl();
	init_env(envp, &shell.env);
	minishell_loop(&shell);
	return (0);
}
