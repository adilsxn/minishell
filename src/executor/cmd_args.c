/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:13:21 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/11 22:13:21 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

static int count_token(t_tree *tree)
{
    int i;
    t_tree *it;

    i = 0;
    it = tree;
    if (!it)
        return (0);
    while (it != NULL)
    {
        i++;
        it = it->right;
    }
    return (i);
}

char **build_av(t_tree *tree)
{
    char **av;
    int len;
    int i;
    t_tree *curr;

    len = count_token(tree);
    av = ft_calloc(len + 1, sizeof(*av));
    if (av == NULL)
        return (NULL);
    curr = tree;
    i = 0;
    while (i < len)
    {
        av[i] = ft_strdup(curr->token);
        curr = curr->right;
        i++;
    }
    av[len + 1] = "\0";
    return (av);
}
