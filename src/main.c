/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:16:54 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/22 15:59:25 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void  minishell_loop(t_tool *shell)
{
	int i;
	char *input;
	t_lexer *lexi = NULL;

	i = -1;
	input = readline("minishell> ");
	input = ft_strtrim(input, " ");
	if (!input || !*input)
	{
		ft_putendl_fd("exit", 1);
		exit (0);
	}
	add_history(input);
	while ((size_t)++i < ft_strlen(input))
	{
		i += len_word(i, input, &shell->lexer);
		if (i == 0)
		{
			ft_error(1, shell);
			return ;
		}
	}
    free(input);
	lexi = shell->lexer;
	while (shell->lexer)
	{
		printf("lexer: %s\n", shell->lexer->str);
		shell->lexer = shell->lexer->next;
	}
	shell->lexer = lexi;
	while (shell->lexer)
	{
		if (shell->lexer->str)
		{
			if (shell->lexer->i == 0 || (shell->lexer->i != 0 && shell->lexer->prev->token != 5))
			{
				if (shell->lexer->str[0] != 39 && shell->lexer->str[ft_strlen(shell->lexer->str) - 1] != 39)
				{
					shell->lexer->str = expander(shell->env, shell->lexer->str);
					shell->lexer->str = del_quotes(shell->lexer->str, '\"');
					printf("expander: %s\n", shell->lexer->str);
				}
				else
				{
					shell->lexer->str = del_quotes(shell->lexer->str, 39);
					printf("lexer: %s\n", shell->lexer->str);
				}
			}
		}
		shell->lexer = shell->lexer->next;
	}
	shell->lexer = lexi;
	shell-> = parser(shell->lexer);
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
    sig_handl();
	init_env(envp, &shell.env);
	minishell_loop(&shell);
	return (0);
}
