/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:38:14 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/07 19:38:14 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

static t_tree *lower(t_tree *root, t_tree *it)
{
    it->right = root;
    return (it);
}

static t_tree *equal(t_tree *root, t_tree *it)
{
    if (it->kind == MINUS || it->kind == PPE
            || (it->heredoc && !it->heredoc))
    {
        it->right = root;
        return (it);
    }
    root->right = tree_insert(root->right, it);
    return (root);
}

static t_tree *greater(t_tree *root, t_tree *it)
{
    if (root->kind == PPE)
    {
        if (root->right != NULL)
            root->left = tree_insert(root->left, it);
        else
            root->right = tree_insert(root->right, it);
    }
    if (root->kind == RDR)
    {
        if (root->left != NULL)
            root->left = tree_insert(root->left, it);
        else
            root->right = tree_insert(root->right, it);
    }
    return (root);
}

t_tree *tree_insert(t_tree *tree, t_tree *it)
{
    t_tree *root;

    root = tree;
    if (tree == NULL)
        return (it);
    if (it->kind < root->kind)
        root = lower(root, it);
    else if (it->kind == root->kind)
        root = equal(root, it);
    else
        root = greater(root, it);
    return (root);
}

