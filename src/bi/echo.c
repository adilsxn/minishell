/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:13:55 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/09/11 12:13:55 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ms_bi_echo(char *input, int nflag)
{
    int i;

    i = 0;
    while (input[i] != 0)
    {
        if (!nflag)
            ft_putstr_fd(input, 1);
        if (nflag)
        {
            ft_putstr_fd(input, 1);
            write(1, " ", 1);
        }
    }
}

