/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:16:54 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/02/12 18:55:58 by matilde          ###   ########.fr       */
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

static bool parse_input(t_tool *shell)
{
    char	*tmp;
	t_lexer	*le;

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
		le = shell->lexer;
		while (le)
		{
			if (le->str)
			{
				if (ft_strequ(shell->lexer->str, "echo"))
				{
					if (quote_assist(le->str, 34) < 2)
						le->str = del_quote(le->str, 39);
					else if (quote_assist(le->str, 39) < 2)
						le->str = del_quote(le->str, 34);
				}
			}
			le = le->next;
		}
       if (has_pipe(shell->lexer) == 1)
            shell->pipes = parser(shell);
       else
           return(exec_cmd(shell), false);
    }
    return (true);
}

int	quote_assist(char *str, int q)
{
	int	i;
	int a;

	i = 0;
	a = 0;
	while (str[i])
	{
		if (str[i] == q)
			a = 1;
		i++;
		if (str[i] && str[i] == q && a == 1)
			return (2);
	}
	return (a);
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
