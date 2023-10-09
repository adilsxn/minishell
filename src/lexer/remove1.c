/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:02:59 by matilde           #+#    #+#             */
/*   Updated: 2023/10/04 19:03:02 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// free because str is malloced
void	*clear_one(t_lexer **lst)
{
	if ((*lst)->str)
		free((*lst)->str);
	free(*lst);
	return (NULL);
}

void	del_first(t_lexer **lst)
{
	t_lexer	*node;

	node = *lst;
	*lst = node->next;
	clear_one(&node);
	if (*lst)
		(*lst)->prev = NULL;
}

//update the prev->next pointer to skip the node deleted
// update lst, pointing to start
void	del_one(t_lexer **lst, int i)
{
	t_lexer	*node;
	t_lexer	*prev;
	t_lexer	*start;

	start = *lst;
	node = start;
	if ((*lst)->i == 1)
	{
		del_first(lst);
		return ;
	}
	while (node && node->i != i)
	{
		prev = node;
		node = node->next;
	}
	if (node)
		prev->next = node->next;
	else
		prev->next = NULL;
	clear_one(&node);
	*lst = start;
}

void	lst_clear(t_lexer **lst)
{
	t_lexer	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->str)
			free((*lst)->str);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
