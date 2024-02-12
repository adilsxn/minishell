/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:13:55 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/02/12 18:21:11 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	is_flag_on(char *str)
{
	int		i;
	bool	nflag;

	nflag = false;
	i = 0;
	if (str[i] != '-'  || str[i + 1] != 'n')
		return (nflag);
	i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] == '\0')
		nflag = true;
	return (nflag);
}

static void	printerx(char **args, bool nflag, int i)
{
	if (args[i] == NULL)
	{
		if (nflag == false)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && nflag == false)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

int	msh_echo(char **args, t_tool *data)
{
	bool	nflag;
	int		i;

	i = 1;
	nflag = false;
	(void)data;
	while (args[i] && is_flag_on(args[i]))
	{
		nflag = true;
		i++;
	}
	printerx(args, nflag, i);
	return (EXIT_SUCCESS);
}
