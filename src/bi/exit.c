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

static bool	is_exit_alone(t_tool *shell)
{
    if (shell->pipes)
        return (false);
    else
        return (true);
}

static bool	overflow(bool *error, int sinal, unsigned long long res)
{
	if ((sinal == 1 && res > LONG_MAX) || (sinal == -1 && res >
			-(unsigned long)LONG_MIN))
		*error = true;
	return (*error);
}

static int	ft_atol(char *str, bool *error)
{
	int					sinal;
	unsigned long long	res;

	res = 0;
	sinal = 1;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	if (*str == '-')
	{
		sinal = -sinal;
		str++;
	}
	while (*str && '0' <= *str && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if (overflow(error, sinal, res))
			break ;
		str++;
	}
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
	bool	alone;
    int exit_;

	error = false;
	alone = is_exit_alone(data);
	if (alone)
		ft_putendl_fd("exit", 1);
	if (!args || !args[1])
		exit_ = 2;
	else
	{
		exit_ = get_code(args[1], &error);
		if (error == true)
			ft_err("exit", args[1], "numeric argument required", 2);
		else if (args[2])
			return(ft_err("exit: too many arguments", NULL, NULL, 1), 1);
	}
	clean_fds();
	clean_data(data, true);
	exit(exit_);
}
