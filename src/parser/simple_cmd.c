/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:06:55 by matilde           #+#    #+#             */
/*   Updated: 2023/10/12 16:40:31 by matilde          ###   ########.fr       */
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
//
// void	cmd_rm_first(t_simple_cmd **lst)
// {
// 	t_simple_cmd	*tmp;

// 	if (!*lst)
// 		return ;
// 	tmp = (*lst)->next;
// 	lst_clear(&(*lst)->redirect);
// 	free(*lst);
// 	*lst = tmp;
// }

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

// t_simple_cmd	*cmd_first(t_simple_cmd *map)
// {
// 	int	i;

// 	i = 0;
// 	if (!map)
// 		return (NULL);
// 	while (map->prev != NULL)
// 	{
// 		map = map->prev;
// 		i++;
// 	}
// 	return (map);
// }
//
// char	**copy_str_array(char **str)
// {
// 	int		size = get_str_array_size(str);
// 	char 	**copy = (char **)malloc(sizeof(char *) * (size + 1));
// 	int		i;

// 	if (!copy)
// 		return (NULL);
// 	i = 0;
// 	while (i++ < size)
// 	{
// 		copy[i] = strdup(str[i]);
// 		if (!copy[i])
// 		{
// 			free_str_array(copy, i);
// 			free(copy);
// 			return NULL;
// 		}
// 	}
// 	copy[size] = NULL;
// 	return (copy);
// }