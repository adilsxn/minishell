/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:41:54 by matilde           #+#    #+#             */
/*   Updated: 2024/01/14 21:40:29 by acuva-nu         ###   ########.fr       */
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
//str is already broken into diffent cmd
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

char	*expander_str(t_tool *tool, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (str[dollar_sign(str) - 2] != '\'' && dollar_sign(str) != 0
		&& str[dollar_sign(str)] != '\0')
	{
		tmp = check_dollar(tool, str);
		free(str);
		str = tmp;
	}
	str = del_quote(str, '\"');
	str = del_quote(str, '\'');
	return (str);
}

//expansion + redirection
t_simple_cmd	*call_expander(t_tool *tool, t_simple_cmd *cmd)
{
	t_lexer	*start;

	cmd->str = expander(tool, cmd->str);
	start = cmd->redirect;
	while (cmd->redirect)
	{
		if (cmd->redirect->token != LESS_LESS)
			cmd->redirect->str = expander_str(tool, cmd->redirect->str);
		cmd->redirect = cmd->redirect->next;
	}
	cmd->redirect = start;
	return (cmd);
}
