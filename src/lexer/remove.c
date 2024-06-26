/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:02:59 by matilde           #+#    #+#             */
/*   Updated: 2024/03/05 18:50:23 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	lst_clear(t_lexer **lst)
{
	t_lexer	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		ft_free((void **)&(*lst)->str);
		ft_free((void **)&(*lst)->str2);
		ft_free((void **)&*lst);
		*lst = tmp;
	}
}

void	*clear_one(t_lexer **lst)
{
	if ((*lst)->str)
	{
		ft_free((void **)&(*lst)->str);
		ft_free((void **)&(*lst)->str2);
	}
	ft_free((void **)&*lst);
	return (NULL);
}

void	del_first(t_lexer **lst)
{
	t_lexer	*node;
	t_lexer	*node1;

	node = *lst;
	*lst = node->next;
	clear_one(&node);
	if (*lst)
		(*lst)->prev = NULL;
	node1 = *lst;
	while (*lst)
	{
		(*lst)->i = (*lst)->i - 1;
		(*lst) = (*lst)->next;
	}
	*lst = node1;
}

static void	del_one1(t_lexer *prev, t_lexer *node)
{
	t_lexer	*current;

	prev->next = node->next;
	current = prev->next;
	while (current)
	{
		current->i = current->i - 1;
		current->prev = prev;
		prev = current;
		current = current->next;
	}
}

// update the prev->next pointer to skip the node deleted
// update lst, pointing to start
void	del_one(t_lexer **lst, int i)
{
	t_lexer	*node;
	t_lexer	*prev;
	t_lexer	*start;

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
		del_one1(prev, node);
	else
		prev->next = NULL;
	clear_one(&node);
	*lst = start;
}

// void	del_1(t_lexer *lst)
// {
// 	if (!lst)
// 		return ;
// 	if (lst->next)
// 		lst->next->prev = lst->prev;
// 	if (lst->prev)
// 		lst->prev->next = lst->next;
// 	else if (lst->next && !lst->prev)
// 		lst->next->next = NULL;
// 	if (lst->str)
// 	{
// 		free(lst->str);
// 		free(lst->str2);
// 		lst->str = NULL;
// 		lst->str2 = NULL;
// 	}
// 	free(lst);
// 	lst = NULL;
// }