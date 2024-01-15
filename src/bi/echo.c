/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:13:55 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/14 23:17:23 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void printerx(int i, char **str, int fd)
{
    while(str[i])
        ft_putstr_fd(str[i++], 1);
            if (str[i])
                ft_putchar_fd(' ', 1);
        
}

int msh_echo(char **args)
{
    int nflag;
    int i;

    i = 1;
    nflag = 1;
    if (args[i] != NULL)
    {
        ft_putchar_fd('\n', 1);
        return (EXIT_SUCCESS);
    }
    if (ft_strequ(args[1], "-n") == 0))
    {
        nflag = 0;
        i++;
    }
    printerx(i, args->str, 1);
    if (nflag)
        ft_putstr_fd("\n", 1);
    return (EXIT_SUCCESS);
}
