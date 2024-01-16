/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:16:54 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/16 17:38:43 by matde-je         ###   ########.fr       */
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
        ft_putendl_fd("exit", 1);
        exit (0);
    }
    add_history(input);
    while ((size_t)++i < ft_strlen(input))
        if (len_word(i, input, &shell->lexer) == -1)
            return ;
    free(input);
    while (shell->lexer) 
    {
        expander(shell->env, shell->lexer->str);
        printf("%s", shell->lexer->str);
        shell->lexer->next = shell->lexer->next;
    }
    // t_lexer *k = shell->lexer;
    // while (k != NULL)
    // {
    //     printf("%s\n", k->str);
    //     k = k->next;
    // }
    shell->tree = parser(shell->lexer);
    tree_exec(shell->tree, shell->env);
    //reset_tool();
}

int main (int ac, char **av, char **envp)
{
    t_tool shell;
    
    shell = (t_tool){NULL, NULL, NULL, NULL};
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
