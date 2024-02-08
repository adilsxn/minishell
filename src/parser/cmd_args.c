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
	int	i;
	t_lexer *it;

	i = 0;
	it = lexi;
	if (!it)
		return (0);
	while (it != NULL)
	{
		if (it->token == PIPE)
			break ;
        if (it->token == 0)
            i++;
		it = it->next;
	}
	return (i);
}

char	**build_av(t_lexer *lexi, int tkn_nbr)
{
	char	**av;
	t_lexer *it;
	int		i;

	it = lexi;
	av = (char **)malloc(sizeof(char *) * (tkn_nbr + 1));
	if (av == NULL)
		return (NULL);
	i = 0;
	while (i < tkn_nbr)
	{
        if (it->token == PIPE)
            break ;
        if (it->token == 0)
               av[i++] = ft_strdup(it->str);
		it = it->next;
	}
	av[tkn_nbr] = NULL;
	return (av);
}
