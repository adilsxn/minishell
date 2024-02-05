/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:41:54 by matilde           #+#    #+#             */
/*   Updated: 2024/02/05 12:47:21 by acuva-nu         ###   ########.fr       */
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
	*str2 = malloc(ft_strlen(str1[0]) + 1);
	if (*str2 != NULL)
    	ft_strlcpy(*str2, str1[0], ft_strlen(str1[0]) + 1);
	else
		return (-1);
	return (len);
}

char	*expander(t_env *env, char *str)
{
	char	**str1;
	t_envy	*ex1;

	ex1 = env->ex;
	ex1 = malloc(sizeof(t_envy));
	if (init_expand(&str, &str1) != NULL)
	{
		ft_free(ex1);
		return (str);
	}
	ex1->len = initialize_expander(&ex1->env2, &ex1->i, &ex1->str2, str1);
	while (str1[ex1->i] != NULL && ex1->len != -1)
	{
		if (tmpcheck(&ex1->tmp, str1, ex1->i) != NULL)
		{
			if (envy(&ex1->env2, env, &ex1->str3, ex1->tmp) == 1)
				loop_help2(&ex1, &ex1->str2, ex1->str3, str1);
			else
				checker(ex1->env2, &ex1->str2, ex1->i);
		}
		else
			ex1->str2 = expander_help1(ex1->len, &ex1->str2, str1, ex1->i);
		ex1->i = loopin(&ex1->env2, &ex1->str3, ex1->tmp, ex1->i);
	}
	return (freer(&ex1, str, str1));
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
            {
				lex->str = expander(env, lex->str);
            }
			else
				lex->str = del_quotes(lex->str, 34);
		}
		lex = lex->next;
	}
	return (lexi);
}
