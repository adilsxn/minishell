/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:12:32 by matilde           #+#    #+#             */
/*   Updated: 2023/10/12 16:33:22 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//count the pipes in lexer_list
void	count_pipes(t_lexer *lexer_list, t_tool *tool)
{
	t_lexer	*tmp;

	tmp = lexer_list;
	tool->pipes = 0;
	while (tmp)
	{
		if (tmp->token == PIPE)
			tool->pipes++;
		tmp = tmp->next;
	}
}

//count words of lexer list before a pipe
int	count_arg(t_lexer *lexer_list)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = lexer_list;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->i > 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

// last command before pipe
// t_lexer	*find_next_cmd(t_lexer *lexer_lst)
// {
// 	while (lexer_lst && lexer_lst->token != PIPE)
// 		lexer_lst = lexer_lst->next;
// 	return (lexer_lst);
// }