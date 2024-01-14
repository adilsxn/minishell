/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:40:39 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/13 16:10:09 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

int minishell_loop(t_tool *shell)
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
