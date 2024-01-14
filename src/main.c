/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:16:54 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/13 14:40:12 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"
#include <stdlib.h>

static void setup_a(int ac, char **av, char **env)
{

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
