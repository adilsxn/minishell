/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:16:54 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/14 19:50:31 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"
#include <stdlib.h>

static int minishell_loop(t_tool *shell)
{
    int i;
    char *input;

    i = -1;
    input = readline("minishell> ");
    input = ft_strtrim(input, " ");
    if (!input || !*input)
    {
        ft_putendl_fd("exit", STDOUT_FILENO);
        exit (EXIT_SUCCESS);
    }
    add_history(input);
    while (++i < ft_strlen(input))
        if (len_word(i, input, &shell->lexer) == -1)
            return (-1);
    free(input);
    parser(shell);
}

int main (int ac, char **av, char **env)
{
    t_tool shell;

    if (ac != 1 || av[1])
    {
        printf("No args accepted\n");
        exit(0);
    }
    shell.env = ft_arrdup(env);
    init_env(env, &shell.our_env);
    minishell_loop(&shell);
    return (0);
}
