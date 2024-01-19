/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:41:54 by matilde           #+#    #+#             */
/*   Updated: 2024/01/19 16:59:52 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *get_key(char *str)
{
	int i;
	i = 0;
	while(str[i] != '\0' && !ft_isspace(str[i]) && str[i] != 47 && str[i] != '"' && str[i] != '\'' && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}
//	char *str;
//str = ft_strchr(str, '$');
// if (str == NULL)
// 	return (NULL);
// if (str != NULL && *str == '$')
// 	str++;

char	*expander(t_env *env, char *str)
{
	char	*tmp;
	t_env *env2;
	char **str1;
	char *str2;
	char *str3;
	int i;

	env2 = NULL;
	i = 0;
	str = del_quotes(str, '\"');
	str1 = ft_split(str, '$');
	str2 = str1[0];
	while(str1[i] != NULL)
	{
		tmp = get_key(str1[i]);
		if (tmp != NULL)
		{
			env2 = get_env(env, tmp);
			if (env2 != NULL)
			{
				str3 = (char *)env2->value;
				if (i > 0)
				{
					str2 = ft_strjoin(str2, str3);
					str2 = ft_strjoin(str2, str1[i] + ft_strlen(tmp));
				}
				else
					str2 = ft_strjoin(str3, str1[i] + ft_strlen(tmp));
			}
		}	
		i++;
		tmp = NULL;
		env2 = NULL;
		str3 = NULL;
	}
	return (str2);
}

// if (tmp2 != NULL)
// {
// 	tmp3 = get_key(tmp2);
// 	if (tmp3 != NULL)
// 	{
// 		env1 = get_env(env, tmp3);
// 		if (env1 != NULL)
// 			tmp4 = ft_strjoin(env2->value, env1->value);
// 		else
// 			tmp4 = ft_strjoin(env2->value, tmp2);
// 	}
// 	else
// 		tmp4 = ft_strjoin(env2->value, tmp2);
// str = tmp4;
// return (str);
//question mark function and loop_if_dollar change the tmp
//i increments after these functions or not if the functions return 0
//i increments after assigning str[i] to tmp2 and then update tmp
// char	*check_dollar(t_env *env, char *str)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*tmp2;
// 	char	*tmp3;
// 	i = 0;
// 	tmp = ft_calloc(1, 1);
// 	while (str[i])
// 	{
// 		i += digit_after_dollar(i, str);
// 		if (str[i] == '$' && str[i + 1] == '?')
// 			i += question_mark(&tmp);
// 		else if (str[i] == '$' && (str[i + 1] != ' ' && (str[i + 1] != '"' 
// 					|| str[i + 2] != '\0')) && str[i + 1] != '\0')
// 			i += loop_dollar_sign(env, str, tmp, i);
// 		else
// 		{
// 			tmp2 = char_to_str(str[i++]);
// 			tmp3 = ft_strjoin(tmp, tmp2);
// 			free(tmp);
// 			tmp = tmp3;
// 			free(tmp2);
// 		}
// 	}
// 	return (tmp);
// }
//after the dollar sign
//env=value
//comparing env with str, str[i] + 1 so its not $
//and -1 so its not the = 
//minus j to be the len after the dollar and before the equal sign
//atribute the value of the env(key) to tmp transforming it to its correspondent
//return an int to increment the i in the original function
// char *	loop_dollar_sign(t_env *env, char *str, char *tmp, int j)
// {
// 	int		final;
// 	(void)	j;
// 	final = 0;
// 	env = get_env(env, get_key(str));
// 	return (env->value);
// 	if (env->key)
// 		final = ft_strlen(env->key) + 1;
// 	if (final == 0)
// 		final = ft_strlen(env->value);
// 	free(tmp);
// 	tmp = (char *)env->value;
// 	return (final);
// }
//export makes a variable available to other processes
//started from the current shell session
//str is already broken into diffent cmd
//quotes are not removed for export command
//char	*tmp;
// if (str[dollar_sign(str) - 2] == '\'' && dollar_sign(str) == 0
// 	&& str[dollar_sign(str)] == '\0')
// 	return (NULL);
// tmp = NULL;
// {
// 	tmp = check_dollar(env, str);
// 	free(str);
// 	str = tmp;
// }
// str = del_quote(str, '\"');
// str = del_quote(str, '\'');
// return (str);