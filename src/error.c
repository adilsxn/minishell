/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:49:56 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/02/22 11:05:36 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free(void **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static char	*join_str(char *str1, char *str2)
{
	char	*tmp;

	if (str2 == NULL)
		return (str1);
	if (str1 == NULL)
		return (ft_strdup(str2));
	tmp = str1;
	str1 = ft_strjoin(tmp, str2);
	ft_free((void **)&tmp);
	return (str1);
}

void	ft_err(char *message, char *detail, char *errorstr, int ret_code)
{
	char	*str;

	str = ft_strdup("minishell: ");
	str = join_str(str, message);
	if (detail != NULL)
		str = join_str(str, ": ");
	str = join_str(str, detail);
	if (errorstr != NULL)
	{
		str = join_str(str, ": ");
		str = join_str(str, errorstr);
	}
	ft_putendl_fd(str, STDERR_FILENO);
	g_last_ret_code = ret_code;
	ft_free((void **)&str);
}


void	ft_err2(char *message, char *detail, char *errorstr)
{
	char	*str;

	str = ft_strdup("minishell: ");
	str = join_str(str, message);
	if (detail != NULL)
		str = join_str(str, ": ");
	str = join_str(str, detail);
	if (errorstr != NULL)
	{
		str = join_str(str, ": ");
		str = join_str(str, errorstr);
	}
	ft_putendl_fd(str, STDERR_FILENO);
	ft_free((void **)&str);
}

char	*syntax_error(int i)
{
	char	*str1;

	str1 = NULL;
	if (i == 1)
		str1 = ft_strjoin("syntax error near unexpected token  `", "|'");
	if (i == 2)
		str1 = ft_strjoin("syntax error near unexpected token  `", ">'");
	if (i == 3)
		str1 = ft_strjoin("syntax error near unexpected token  `", ">>'");
	if (i == 4)
		str1 = ft_strjoin("syntax error near unexpected token  `", "<'");
	if (i == 5)
		str1 = ft_strjoin("syntax error near unexpected token  `", "<<'");
	return (str1);
}
