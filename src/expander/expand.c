/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:41:54 by matilde           #+#    #+#             */
/*   Updated: 2024/02/26 18:44:59 by acuva-nu         ###   ########.fr       */
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

int	initialize_expander(t_env **env2, int *i, char **str2, char **str1)
{
	int	len;

	len = 0;
	*env2 = NULL;
	*i = 0;
	while (str1[len])
		len++;
	*str2 = malloc(ft_strlen(str1[0]) + 1);
	if (*str2 != NULL)
		ft_strlcpy(*str2, str1[0], ft_strlen(str1[0]) + 1);
	else
		return (-1);
	return (len);
}

char	*init_expand(char **str, char ***str1)
{
	if ((*str)[0] == 39)
	{
		del_quote(*str, '\'');
		return (*str);
	}
	*str1 = ft_split2(*str, '$');
	return (NULL);
}

char	*expander(t_env *env, char *str)
{
	char	**str1;
	t_env1	*env1;

	env1 = env->env1;
	env1 = malloc(sizeof(t_env1));
	if (init_expand(&str, &str1) != NULL)
	{
		ft_free((void **)&env1);
		return (str);
	}
	env1->len = initialize_expander(&env1->env2, &env1->i, &env1->str2, str1);
	while (str1[env1->i] != NULL && env1->len != -1)
	{
		if (tmpcheck(&env1->tmp, str1, env1->i) != NULL)
		{
			if (env1_func(&env1->env2, env, &env1->str3, env1->tmp) == 1)
				loop_help2(&env1, &env1->str2, env1->str3, str1);
			else
				checker(env1, -1, str1);
		}
		else
			env1->str2 = expander_help1(env1->len, &env1->str2, str1, env1->i);
		env1->i = loopin(&env1->env2, &env1->str3, env1->tmp, env1->i);
	}
	return (freer(&env1, str, str1));
}

t_lexer	*expander2(t_env *env, t_lexer *lexi)
{
	t_lexer	*lex;

	lex = lexi;
	if (!env)
		return (lexi);
	while (lex)
	{
		if (lex->str)
		{
			if ((lex->i == 0 && lex->token != 5) || (lex->i > 0 && (!lex->prev->token
						|| lex->prev->token != 5)))
			{
				lex->str = expander(env, lex->str);
			}
		}
		lex = lex->next;
	}
	return (lexi);
}
