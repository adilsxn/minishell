/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:02:59 by matilde           #+#    #+#             */
/*   Updated: 2024/01/23 12:03:56 by matde-je         ###   ########.fr       */
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
	t_lexer	*node1;

	printf("lst i: %i\n", (*lst)->i);
	node = *lst;
	*lst = node->next;
	clear_one(&node);
	if (*lst)
		(*lst)->prev = NULL;
	node1 = *lst;
	while (*lst)
	{
		(*lst)->i = (*lst)->i -1;
		printf("lst i: %i\n", (*lst)->i);
		(*lst) = (*lst)->next;
	}
	*lst = node1;
}

//update the prev->next pointer to skip the node deleted
// update lst, pointing to start
void	del_one(t_lexer **lst, int i)
{
	t_lexer	*node;
	t_lexer	*prev;
	t_lexer	*start;
	t_lexer *current;

	start = *lst;
	node = start;
	if ((*lst)->i == i)
	{
		del_first(lst);
		return ;
	}
	while (node && node->i != i)
	{
		prev = node;
		node = node->next;
	}
	if (node->next)
	{
		prev->next = node->next;
		current = prev->next;
		while (current)
		{
			current->i = current->i -1;
			current->prev = prev;
        	prev = current;
			current = current->next;
		}
	}
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
