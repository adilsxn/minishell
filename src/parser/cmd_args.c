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
		if (it->token != 0)
			break ;
		i++;
		it = it->next;
	}
	return (i);
}

char	**build_av(t_lexer *lexi)
{
	char	**av;
	t_lexer *it;
	int		len;
	int		i;

	it = lexi;
	len = count_token(lexi);
	av = (char **)malloc(sizeof(char *) * (len + 1));
	if (av == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (it->token != 0)
			break ;
        if(it->str == NULL)
            av[i++] = ft_strdup("");
        else
            av[i++] = ft_strdup(it->str);
		it = it->next;
	}
	av[len] = NULL;
	return (av);
}
