/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:48:03 by matilde           #+#    #+#             */
/*   Updated: 2024/01/05 22:11:01 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void assign_type(t_token token, t_order type, t_tree *it)
{
    it->kind = type;
    it->heredoc = false;
    if (token == LESS)
        it->fn = rdir_i;
    else if (token == GREAT)
        it->fn = rdir_o;
    else if (token == LESS_LESS)
    {
        it->fn = hdoc;
        it->heredoc = true;
    }
    else if (token == GREAT_GREAT)
        it->fn = appnd;
    else if (type == PPE)
        it->fn = exec_pipe;
    else 
        it->fn = exec_cmd;
}

t_tree *make_leaf(t_lexer *lexem)
{
    t_tree *it;

    it = malloc(sizeof(*it));
    if (it == NULL)
        return (NULL);
    if (lexem->token == LESS)
        assign_type(LESS, RDR, it);
    else if (lexem->token == GREAT)
        assign_type(GREAT, RDR, it); 
    else if (lexem->token == GREAT_GREAT)
        assign_type(GREAT_GREAT, RDR, it);
    else if (lexem->token == LESS_LESS)
        assign_type(LESS_LESS, RDR, it);
    else if (lexem->token == PIPE)
        assign_type(PIPE, PPE, it);
    else
        assign_type(TWORD, CMD, it);
    it->root = false;
    if (lexem->str != NULL)
        it->token = ft_strdup(lexem->str);
    it->left = NULL;
    it->right = NULL;
    return (it);
}

void tree_delete(t_tree *tree)
{
    if (tree == NULL)
        return ;
    tree_delete(tree->left);
    tree_delete(tree->right);
    free(tree);
}

t_tree* parser(t_lexer *lexems)
{
    t_tree *tree;
    t_tree *it;
    t_lexer *i;

    tree = NULL;
    it = NULL;
    i = lexems;
    while(i != NULL)
    {
        it = make_leaf(i);
        if (it == NULL)
            perror("Error: Parsing ->");
        tree = tree_insert(tree, it);
        i = i->next;
    }
    tree->root  = true;
    return (tree);
}
