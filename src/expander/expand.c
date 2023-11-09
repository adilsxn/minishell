/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:41:54 by matilde           #+#    #+#             */
/*   Updated: 2023/11/09 18:28:55 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//question mark function and loop_if_dollar change the tmp
//i increments after these functions or not if the functions return 0
//i increments after assigning str[i] to tmp2 and then update tmp
char	*check_dollar(t_tool *tool, char *str)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	i = 0;
	tmp = ft_calloc(1, 1);
	while (str[i])
	{
		i += digit_after_dollar(i, str);
		if (str[i] == '$' && str[i + 1] == '?')
			i += question_mark(&tmp);
		else if (str[i] == '$' && (str[i + 1] != ' ' && (str[i + 1] != '"' \
					|| str[i + 2] != '\0')) && str[i + 1] != '\0')
			i += loop_dollar_sign(tool, str, &tmp, i);
		else
		{
			tmp2 = char_to_str(str[i++]);
			tmp3 = ft_strjoin(tmp, tmp2);
			free(tmp);
			tmp = tmp3;
			free(tmp2);
		}
	}
	return (tmp);
}

//after the dollar sign
//env=value
//comparing env with str, str[i] + 1 so its not $
//and -1 so its not the = 
//minus j to be the len after the dollar and before the equal sign
//atribute the value of the env(key) to tmp transforming it to its correspondent
//return an int to increment the i in the original function
int	loop_dollar_sign(t_tool *tool, char *str, char **tmp, int j)
{
	int		i;
	int		final;
	char	*tmp2;
	char	*tmp3;

	i = 0;
	final = 0;
	while (tool->env[i])
	{
		if (ft_strncmp(str + j + 1, tool->env[i], \
			equal_sign(tool->env[i]) - 1) == 0 && after_dollar_len(str, j) \
			- j == (int)equal_sign(tool->env[i]))
		{
			tmp2 = ft_strdup(tool->env[i] + equal_sign(tool->env[i]));
			tmp3 = ft_strjoin(*tmp, tmp2);
			free(*tmp);
			*tmp = tmp3;
			free(tmp2);
			final = equal_sign(tool->env[i]);
		}
		i++;
	}
	if (final == 0)
		final = after_dollar_len(str, j) - j;
	return (final);
}

//export makes a variable available to other processes
//started from the current shell session
//str is already broken into diffent cmds
char	**expander(t_tool *tool, char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] != NULL)
	{
		if (str[i][dollar_sign(str[i]) - 2] != '\'' && dollar_sign(str[i]) != 0
			&& str[i][dollar_sign(str[i])] != '\0')
		{
			tmp = check_dollar(tool, str[i]);
			free(str[i]);
			str[i] = tmp;
		}
		if (ft_strncmp(str[0], "export", ft_strlen(str[0]) - 1) != 0)
		{
			str[i] = del_quote(str[i], '\"');
			str[i] = del_quote(str[i], '\'');
		}
		i++;
	}
	return (str);
}
