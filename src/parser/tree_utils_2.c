/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:16:34 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/09 17:16:34 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

static bool is_syntax_mixed(t_tree *tree)
{
    t_tree *left;
    t_tree *right;

    left = tree->left;
    right = tree->right;
    if (!tree->root && tree->kind == PPE)
        if (left != NULL && left->kind == RDR)
            return (true);
    if (tree->kind == PPE)
    {
        if (left != NULL && left->heredoc)
            return (true);
        if (right != NULL && right->heredoc)
            return (true);
    }
    return (false);
}

bool is_complete(t_tree *tree)
{
    if (tree == NULL)
        return (true);
    if (tree->kind == PPE || tree->kind == RDR)
        if (tree->left == NULL)
            return (false);
    if (is_syntax_mixed(tree))
        return (false);
    if (!is_complete(tree->right) || !is_complete(tree->left))
        return (false);
    return (true);
}

static void rollback(int fd0, int fd1)
{
    int ret;

    ret = dup2(fd0, STDIN_FILENO);
    if (ret == -1)
        printf("Error while returning fd's");
    ret = dup2(fd1, STDOUT_FILENO);
    if (ret == -1)
        printf("Error while returning fd's");
    close(fd0);
    close(fd1);
}

void tree_exec(t_tree *tree, t_env *env)
{
    int fd[2];

    fd[0] = dup(STDIN_FILENO);
    fd[1] = dup(STDOUT_FILENO);
    if (fd[0] == -1 || fd[1] == -1)
        printf("Error while duping std fd's");
    if (is_complete(tree) == false)
        printf("Syntax error\n");
    else
        tree->f(tree, env);
    rollback(fd[0], fd[1]);
}

