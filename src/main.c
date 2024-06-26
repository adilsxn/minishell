/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:16:54 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/04/04 21:37:59 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// if (ac != 1)
// 	ft_err("Non interative mode not available", NULL, NULL, 1);
static bool	parse_noninteractive(t_tool *shell, char **ni_input, int i)
{
	char	*tmp;

	while (ni_input[++i])
	{
		tmp = ft_strdup(ni_input[i]);
		shell->arg = ft_strtrim(tmp, " ");
		free(tmp);
		shell->lexer = lexer(shell->arg, shell->lexer, shell);
		if (shell->lexer)
		{
			lexer_redux(&shell->lexer);
			shell->lexer = expander2(shell->env, shell->lexer);
			quote_help(shell->lexer);
			parse_heredoc(shell->lexer, shell->env);
			if (has_pipe(shell->lexer) == 1)
				shell->pipes = parser(shell);
			if (has_pipe(shell->lexer) == 1)
				exec_pipe(shell);
			else
				exec_cmd(shell);
		}
		clean_data(shell, false);
	}
	return (true);
}

volatile int	g_last_ret_code = 0;

static bool	parse_input(t_tool *shell)
{
	char	*tmp;

	signal_handler(sig_new_prompt, SIGINT);
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
		parse_heredoc(shell->lexer, shell->env);
		if (has_pipe(shell->lexer) == 1)
			shell->pipes = parser(shell);
		else
			return (exec_cmd(shell), false);
	}
	return (true);
}

int	main(int ac, char **av, char **envp)
{
	t_tool	shell;
	char	**ni_arg;

	ft_bzero(&shell, sizeof(t_tool));
	shell = (t_tool){NULL, NULL, NULL, NULL, false, NULL};
	if (ac == 3 && ft_strequ(av[1], "-c") && av[2])
	{
		ni_arg = ft_split(av[2], ';');
		if (!ni_arg)
			exit(EXIT_FAILURE);
		shell.env = init_env(envp);
		shell.ninter = true;
		parse_noninteractive(&shell, ni_arg, -1);
		clean_data(&shell, true);
		free_array(ni_arg);
		return (g_last_ret_code);
	}
	shell.env = init_env(envp);
	while (1)
	{
		if (parse_input(&shell) == true)
			exec_pipe(&shell);
		clean_data(&shell, false);
	}
	return (g_last_ret_code);
}
