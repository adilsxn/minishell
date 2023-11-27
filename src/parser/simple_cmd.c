/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:06:55 by matilde           #+#    #+#             */
/*   Updated: 2023/11/24 17:15:25 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_simple_cmd	*cmd_new(char **str, int nb_redirect, t_lexer *redirect)
{
	t_simple_cmd	*new_element;

	new_element = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (!new_element)
		return (0);
	new_element->str = str;
	new_element->nb_redirect = nb_redirect;
	new_element->redirect = redirect;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

void	add_cmd(t_simple_cmd **lst, t_simple_cmd *new)
{
	t_simple_cmd	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	cmd_clear(t_simple_cmd **lst)
{
	t_simple_cmd	*tmp;
	t_lexer			*redirect_tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		redirect_tmp = (*lst)->redirect;
		lst_clear(&redirect_tmp);
		if ((*lst)->str)
			free((*lst)->str);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_simple_cmd	*first_simple_cmd(t_simple_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->prev != NULL)
		cmd = cmd->prev;
	return (cmd);
}
