/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:37:34 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/09/14 22:37:34 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_atol(char *str, bool *error)
{
	int					sinal;
	unsigned long long	res;

	res = 0;
	sinal = 1;
	while (*str == ' ' || (9 <= *str && *str <= 13))
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sinal = -sinal;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (res > LONG_MAX)
		*error = true;
	return ((int)(res * sinal));
}

static int	get_code(char *str, bool *error)
{
	unsigned long long	i;

	if (str == NULL)
		return (g_last_ret_code);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		*error = true;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		*error = true;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i]))
			*error = true;
		i++;
	}
	i = ft_atol(str, error);
	return (i % 256);
}

int	msh_exit(char **args, t_tool *data)
{
	bool	error;
	int		exit_code;

	if (!args || !args[1])
		exit_code = g_last_ret_code;
	else
	{
		exit_code = get_code(args[1], &error);
		if (error == true)
		{
			exit_code = 2;
			return (ft_err("exit: non numeric arg", args[1]), exit_code);
		}
		else if (args[2])
			return (ft_err("exit: too many arguments", args[1]), 1);
	}
	ft_putendl_fd("exit", 2);
	clean_fds();
	clean_data(data, true);
	printf("hi\n");
	exit(exit_code);
	printf("hi1\n");
}
