/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:16:54 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/16 10:50:05 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static void  minishell_loop(t_tool *shell)
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
    while ((size_t)++i < ft_strlen(input))
        if (len_word(i, input, &shell->lexer) == -1)
            return ;
    free(input);
    //expander called here
    // t_lexer *k = shell->lexer;
    // while (k != NULL)
    // {
    //     printf("%s\n", k->str);
    //     k = k->next;
    // }
    shell->tree = parser(shell->lexer);
    tree_exec(shell->tree, shell->env);
    //reset_tool
}

int main (int ac, char **av, char **envp)
{
    t_tool shell;

    if (ac != 1 || av[1])
    {
        printf("No args accepted\n");
        exit(0);
    }
    //init_tool
    init_env(envp, &shell.env);
    minishell_loop(&shell);
    return (0);
}
