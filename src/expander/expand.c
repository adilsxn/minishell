/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:41:54 by matilde           #+#    #+#             */
/*   Updated: 2024/01/23 22:17:47 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_key(char *str)
{
	int		i;
	char	*str1;

	str1 = ft_strchr(str, '$');
	if (str1 == NULL)
		return (NULL);
	if (str1 != NULL && *str1 == '$')
		str1++;
	i = 0;
	while(str1[i] != '\0' && !ft_isspace(str1[i]) && str1[i] != 47 \
	&& str1[i] != '"' && str1[i] != '\'' && str1[i] != '=')
		i++;
	return (ft_substr(str1, 0, i));
}

// char	*expander_aux(t_env *env, char *str2, char **str1, int i)
// {
// 	char *tmp;
// 	t_env *env2;
// 	char *str3;
	
// 	tmp = get_key(str1[i]);
// 	if (tmp != NULL)
// 	{
// 		env2 = get_env(env, tmp);
// 		if (env2 != NULL)
// 		{
// 			str3 = (char *)env2->value;
// 			if (i > 0 && str2 != NULL)
// 				str2 = double_strj(str2, str3, str1[i] + ft_strlen(tmp) + 1);
// 			else
// 				str2 = ft_strjoin(str3, str1[i] + ft_strlen(tmp) + 1);
// 		}
// 		else
// 			if (i == 0)
// 				str2 = NULL;
// 	}
// 	else
// 		str2 = expander_help1(str2, str1, i);
// 	i = loopin(&env2, &str3, tmp, i);
// 	return (str2);
// }

// char	*expander(t_env *env, char *str2, char **str1)
// {
// 	t_env	*env2;
// 	int		i;
	
// 	env2 = NULL;
// 	i = 0;
// 	while(str1[i] != NULL)
// 	{
// 		str2 = expander_aux(env, str2, str1, i);
// 	}
// 	free_array(str1);
// 	return (str2);
// }

// char	*expander21(t_env *env, t_lexer *lexi, t_lexer *lex)
// {
// 	char	**str1;
// 	char	*str2;

// 	lexi->str = del_quotes(lexi->str, '\"');
// 	if (lexi->str[0] == 39)
// 	{
// 		lexi->str = del_quotes(lexi->str, '\'');
// 		return (lex->str);
// 	}
// 	str1 = ft_split2(lexi->str, '$');
// 	str2 = str1[0];
// 	lexi->str = expander(env, str2, str1);
// 	return (lexi->str);
// }

char	*expander_help1(int len, char *str2, char **str1, int i)
{
	if (len == 1)
		str2 = ft_strdup(str2);
	else if (i > 0 && str2 != NULL)
		str2 = ft_strjoin(str2, str1[i]);
	return (str2);
}

int	loopin(t_env **env2, char **str3, char *tmp, int i)
{
	i++;
	free(tmp);
	*env2 = NULL;
	*str3 = NULL;
	return (i);
}

char	*double_strj(char *str2, char *str3, char *str1)
{
	str2 = ft_strjoin(str2, str3);
	if (str2)
		str2 = ft_strjoin(str2, str1);
	return (str2);
}

void loop_help1(t_env *env2, char **str3)
{
	if (env2 != NULL)
		*str3 = (char *)env2->value;
}

void loop_help2(int	*i, char	**str2, char	*str3, char	**str1)
{
	if (*i > 0 && *str2 != NULL)
	{
		*str2 = ft_strjoin(*str2, str3);
		*str2 = ft_strjoin(*str2, str1[*i] + ft_strlen(get_key(str1[*i])) + 1);
	}
	else
		*str2 = ft_strjoin(str3, str1[*i] + ft_strlen(get_key(str1[*i])) + 1);
	
}

int initialize_expander(t_env	**env2, int	*i, char	**str2, char	**str1)
{
	int len;

	len = 0;
	*env2 = NULL;
	*i = 0;
	while(str1[len])
		len++;
	*str2 = str1[0];
	return (len);
}
char	*init_expand(char **str, char	***str1)
{
	*str = del_quotes(*str, '\"');
	if (*str[0] == 39)
	{
		del_quotes(*str, '\'');
		return (*str);
	}
	*str1 = ft_split2(*str, '$');
	return (NULL);
}

char	*expander(t_env *env, char *str)
{
	t_env	*env2;
	char	*str2;
	char	*str3;
	int		i;
	char	**str1;
	int		len;

	if (init_expand(&str, &str1) != NULL)
		return (str);
	len = initialize_expander(&env2, &i, &str2, str1);
	while(str1[i] != NULL)
	{
		if (get_key(str1[i]) != NULL)
		{
			env2 = get_env(env, get_key(str1[i]));
			loop_help1(env2, &str3);
			if (env2 != NULL)
				loop_help2(&i, &str2, str3, str1);
			if (get_key(str1[i]) != NULL && (i == 0) && env2 == NULL)
				str2 = NULL;
		}
		else
			str2 = expander_help1(len, str2, str1, i);
		i = loopin(&env2, &str3, get_key(str1[i]), i);
	}
	free_array(str1);
	return (str2);
}

t_lexer	*expander2(t_env *env, t_lexer *lexi)
{
	t_lexer	*lex;

	lex = lexi;
	while (lexi)
	{
		if (lexi->str)
		{
			if (lexi->i == 0 || (lexi->i > 0 \
			&& (!lexi->prev->token || lexi->prev->token != 5)))
				lexi->str = expander(env, lexi->str);
			else
				lexi->str = del_quotes(lexi->str, 34);
		}
		lexi = lexi->next;
	}
	return (lex);
}	

// char	*expander2(t_env *env, char *str)
// {
// 	int i;
// 	char	*str1;
// 	char	*str2;
// 	char	*str3;
// 	char	*str4;
// 	int e;
// 	int trig;
// 	int trig1i;
// 	int token;

// 	i = -1;
// 	trig = 0;
// 	trig1i = 0;
// 	while(str[++i])
// 	{
// 		if (check_token(str[i], str[i + 1]) == 5)
// 		{
// 			str1 = ft_substr(str, 0, i);
// 			str1 = expander(env, str1);
// 			trig = 1;
// 			token = i;
// 			i += 2;
// 			while (str[++i])
// 			{
// 				if (str[i] == ' ' || check_token(str[i], str[i + 1]) != 0)
// 				{
// 					str2 = ft_substr(str, token, i - token);
// 					str2 = del_quotes(str2, 34);
// 					str3 = ft_substr(str, i, ft_strlen(str));
// 					str4 = ft_strjoin(str1, str2);
// 					free(str1);
// 					free(str);
// 					str = ft_strjoin(str4, str3);
// 					trig1i = i;
// 					trig = 0;
// 					printf("str: %s\n", str);
// 					free(str2);
// 					free(str3);
// 					free(str4);
// 					printf("str: %s\n", str);
// 					break ;
// 				}
// 			}
// 		}
// 		else if (check_token(str[i], str[i + 1]) != 0 && check_token(str[i], str[i + 1]) != 5 && trig == 0)
// 		{
// 			e = i;
// 			while(str[i])
// 			{
// 				if (check_token(str[i], str[i + 1]) != 0)
// 					break ;
// 				i++;
// 			}
// 			str2 = ft_substr(str, e, i);
// 			i = e;
// 			str3 = expander(env, str2);
// 			str = ft_strjoin(str, str);
// 			trig1i = i;
// 		}
// 		if (!str[i + 1] && trig == 0)
// 		{
// 			printf("str1: %s\n", str);
// 			str1 = expander(env, ft_substr(str, trig1i, i));
// 			str2 = ft_substr(str, 0, trig1i);
// 			free(str);
// 			str = ft_strjoin(str2, str1);
// 			free(str1);
// 			printf("str1: %s\n", str);
// 		}
// 	}
// 	printf("expander: %s\n", str);
// 	return (str);
// }
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