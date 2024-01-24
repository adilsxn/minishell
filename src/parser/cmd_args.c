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

	i = 0;
	if (!lexi)
		return (0);
	while (lexi != NULL)
	{
		if (lexi->token == PIPE)
			break ;
		if (lexi->str != NULL)
			i++;
		lexi = lexi->next;
	}
	return (i);
}

char	**build_av(t_lexer *lexi)
{
	char	**av;
	int		len;
	int		i;

	len = count_token(lexi);
	av = ft_calloc(len + 1, sizeof(*av));
	if (av == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (lexi->token == PIPE)
			break ;
		if (lexi->str != NULL)
			av[i++] = lexi->str;
		lexi = lexi->next;
	}
	av[len + 1] = "\0";
	return (av);
}
