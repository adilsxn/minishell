/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:41:54 by matilde           #+#    #+#             */
/*   Updated: 2024/01/25 11:48:52 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	loopin(t_env **env2, char **str3, char *tmp, int i)
{
	i++;
	free(tmp);
	*env2 = NULL;
	*str3 = NULL;
	return (i);
}

void	loop_help1(t_env *env2, char **str3)
{
	if (env2 != NULL)
		*str3 = (char *)env2->value;
}

int	initialize_expander(t_env **env2, int *i, char **str2, char **str1)
{
	int	len;

	len = 0;
	*env2 = NULL;
	*i = 0;
	while (str1[len])
		len++;
	*str2 = str1[0];
	return (len);
}

char	*expander(t_env *env, char *str)
{
	t_envy	*ex;
	char	**str1;
	char	*ret;

	ex = malloc(sizeof(t_envy));
	if (init_expand(&str, &str1) != NULL)
		return (str);
	ex->len = initialize_expander(&ex->env2, &ex->i, &ex->str2, str1);
	while (str1[ex->i] != NULL)
	{
		if (tmpcheck(&ex->tmp, str1, ex->i) != NULL)
		{
			if (envy(&ex->env2, env, &ex->str3, ex->tmp) == 1)
				loop_help2(&ex->i, &ex->str2, ex->str3, str1);
			checker(ex->env2, &ex->str2, ex->i);
		}
		else
			ex->str2 = expander_help1(ex->len, ex->str2, str1, ex->i);
		ex->i = loopin(&ex->env2, &ex->str3, ex->tmp, ex->i);
	}
	free_array(str1);
	ret = ft_strdup(ex->str2);
	free(ex->str2);
	freer(ex, str);
	return (ret);
}

t_lexer	*expander2(t_env *env, t_lexer *lexi)
{
	t_lexer	*lex;

	lex = lexi;
	while (lex)
	{
		if (lex->str)
		{
			if (lex->i == 0 || (lex->i > 0 && (!lex->prev->token \
						|| lex->prev->token != 5)))
				lex->str = expander(env, lex->str);
			else
				lex->str = del_quotes(lex->str, 34);
		}
		lex = lex->next;
	}
	return (lexi);
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
// 		else if (check_token(str[i], str[i + 1]) != 0
//		&& check_token(str[i], str[i + 1]) != 5 && trig == 0)
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