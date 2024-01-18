/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:16:54 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/17 16:29:23 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void  minishell_loop(t_tool *shell)
{
	int i;
	char *input;
	// t_lexer *lexi = NULL;

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
	/* lexi = shell->lexer;
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
					printf("expander: %s\n", shell->lexer->str);
				}
			}
		}
		shell->lexer = shell->lexer->next;
	}
	shell->lexer = lexi;
 */
	// t_lexer *k = shell->lexer;
	// while (k != NULL)
	// {
	//     printf("%s\n", k->str);
	//     k = k->next;
	// }
	shell->tree = parser(shell->lexer);
	free(shell->lexer);
	tree_exec(shell->tree, shell->env);
	//reset_tool();
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
	//init_tool
	//setup_sgnl();
	init_env(envp, &shell.env);
	minishell_loop(&shell);
	return (0);
}
