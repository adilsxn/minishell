/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:42:29 by matilde           #+#    #+#             */
/*   Updated: 2023/11/09 18:26:55 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_var(t_tool *tool, char *str)
{
	int	i;

	i = 0;
	if (str[equal_sign(str)] == '\"')
		del_quote(str, '\"');
	if (str[equal_sign(str)] == '\'')
		del_quote(str, '\'');
	while (tool->env[i])
	{
		if (ft_strncmp(tool->env[i],
				str, equal_sign(tool->env[i])) == 0)
		{
			free(tool->env[i]);
			tool->env[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_param(char *str)
{
	int	i;

	i = 0;
	if (str[0] > 47 && str[0] < 58)
		return (export_error(str));
	if (equal_sign(str) == 0)
		return (1);
	if (str[0] == '=')
		return (export_error(str));
	while (str[i] != '=')
	{
		if (check_identifier(str[i]) == 1)
			return (export_error(str));
		i++;
	}
	return (0);
}

char	**loop_add_var(char **array, char **final, char *str)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		if (array[i + 1] == NULL)
		{
			final[i] = ft_strdup(str);
			final[i + 1] = ft_strdup(array[i]);
		}
		else
			final[i] = ft_strdup(array[i]);
		if (final[i] == NULL)
		{
			free_array(final);
			return (final);
		}
		i++;
	}
	return (final);
}

char	**add_var(char **array, char *str)
{
	char	**final;
	size_t	i;

	i = 0;
	if (str[equal_sign(str)] == '\"')
		del_quote(str, '\"');
	if (str[equal_sign(str)] == '\'')
		del_quote(str, '\'');
	while (array[i] != NULL)
		i++;
	final = ft_calloc(sizeof(char *), i + 2);
	if (!final)
		return (NULL);
	i = 0;
	loop_add_var(array, final, str);
	return (final);
}

//export explicitly
int	exportation(t_tool *tool, t_simple_cmd *cmd)
{
	char	**tmp;
	int		i;

	i = 1;
	if (!cmd->str[1] || cmd->str[1][0] == '\0')
		envi(tool);
	else
	{
		while (cmd->str[i])
		{
			if (check_param(cmd->str[i]) == 0
				&& check_var(tool, cmd->str[i]) == 0)
			{
				if (cmd->str[i])
				{
					tmp = add_var(tool->env, cmd->str[i]);
					free_array(tool->env);
					tool->env = tmp;
				}
			}
			i++;
		}
	}
	return (0);
}
