/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:13:21 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/11 22:13:21 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_token(t_lexer *lexi)
{
	int		i;
	t_lexer	*it;

	i = 0;
	it = lexi;
	if (!it)
		return (0);
	while (it != NULL)
	{
		if (it->token == PIPE)
			break ;
		if (!it->token && it->str && ft_strchr(it->str, ' '))
			if (!ft_strchr(it->str2, '\'') && !ft_strchr(it->str2, '"')
				&& ft_strchr(it->str, '-'))
				i++;
		if (it->token == 0 && it->str)
			i++;
		it = it->next;
	}
	return (i);
}

int	get_mixed_cmd(char **av, t_lexer *it, int *tkn_nbr)
{
	int		i;
	char	**tmp_av;

	i = 0;
	if (ft_strchr(it->str2, '\'') || ft_strchr(it->str2, '"')
		|| !ft_strchr(it->str, '-'))
		return (1);
	tmp_av = ft_split(it->str, ' ');
	while (i < ft_wordcount(it->str, ' '))
	{
		av[*tkn_nbr] = ft_strdup(tmp_av[i]);
		i++;
		(*tkn_nbr)++;
	}
	free_arr(tmp_av);
	return (0);
}

void	build_av_helper(int *i, int *j, char **av, t_lexer *it)
{
	if (it->token == 0 && it->str != NULL)
	{
		if (ft_strchr(it->str, ' '))
			*j = get_mixed_cmd(av, it, i);
		if (*j)
			av[*i] = ft_strdup(it->str);
		(*i)++;
	}
	it = it->next;
}

char	**build_av(t_lexer *lexi, int tkn_nbr)
{
	int		i;
	int		j;
	t_lexer	*it;
	char	**av;

	it = lexi;
	j = 1;
	if (tkn_nbr == 0)
		return (NULL);
	av = (char **)malloc(sizeof(char *) * (tkn_nbr + 1));
	if (av == NULL)
		return (NULL);
	i = 0;
	while (i < tkn_nbr)
	{
		if (it->token == PIPE)
			break ;
		if (it->token == 0 && it->str != NULL)
		{
			if (ft_strchr(it->str, ' '))
				j = get_mixed_cmd(av, it, &i);
			if (j)
				av[i] = ft_strdup(it->str);
			i++;
		}
		it = it->next;
	}
	av[tkn_nbr] = NULL;
	return (av);
}
