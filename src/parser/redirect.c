/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:06:43 by matilde           #+#    #+#             */
/*   Updated: 2023/11/11 19:20:14 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//redirect has str (cmd) and the token ( > or < or >> or <<) (redirect)
//and then remove from lexer, since its already in redirect
//only accesible in parsertool redirect
int	add_new_redirect(t_lexer *tmp, t_parser_tool *parser_tool)
{
	int		i;
	int		i1;
	int		i2;

	i = new_node(ft_strdup(tmp->next->str), tmp->token, &parser_tool->redirect);
	if (i == -1)
		return (ft_error(0, parser_tool->tool));
	i1 = tmp->i;
	i2 = tmp->next->i;
	del_one(&parser_tool->lexer, i1);
	del_one(&parser_tool->lexer, i2);
	parser_tool->nb_redirect++;
	return (0);
}

//pipes are not redirect
//if theres nothing after redirect token then error
//if redirect token, then add new redirect and rm redirect again
//token is already defined as < or <<
//rm redirect tokens from the lexer to process and handle them separately
void	rm_redirect(t_parser_tool *parser_tool)
{
	t_lexer	*tmp;

	tmp = parser_tool->lexer;
	while (tmp && tmp->token == 0)
		tmp = tmp->next;
	if (!tmp || tmp->token == PIPE)
	{
		return ;
	}
	if (!tmp->next)
		ft_error(0, parser_tool->tool);
	if (tmp->next->token)
	{
		double_token_error(parser_tool->tool);
	}
	if ((tmp->token >= GREAT && tmp->token <= LESS_LESS))
		add_new_redirect(tmp, parser_tool);
	rm_redirect(parser_tool);
}
