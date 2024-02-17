/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:48:49 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/02/17 10:48:49 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

bool	name_heredoc_file(t_rdr *rdr)
{
	static int	i;
	char		*number;
	t_rdr		*it;

	if (i == 0) 
		i = 0;
	it = rdr;
	number = ft_itoa(i);
	if (!number)
		return (ft_err("heredoc failed", NULL, NULL, 1), false);
	free(it->value);
	it->value = ft_strjoin(HD_FILE, number);
	i++;
	ft_free((void **)&number);
	return (true);
}

bool	delim_has_quotes(char *str)
{
	int	i;
	int	nbr_quotes;

	i = 0;
	nbr_quotes = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			nbr_quotes++;
		i++;
	}
	if (nbr_quotes >= 2)
		return (true);
	return (false);
}

