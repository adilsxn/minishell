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


static void assign_type(t_order type, t_tree *it, bool hdflag)
{
    extern void exec_rdr(t_tree *tree, t_env* env);
    extern void exec_ppe(t_tree *tree, t_env* env);    
    extern void exec_cmd(t_tree *tree, t_env* env);

    it->kind = type;
    if (type == RDR)
        it->f = exec_rdr;
    else if (type == PPE)
        it->f = exec_ppe;
    else 
        it->f = exec_cmd;
    if (hdflag == true)
        it->heredoc = true;
    else
        it->heredoc = false;
}


t_tree *make_leaf(t_lexer *lexem)
{
    t_tree *it;
    char *content;

    it = malloc(sizeof(*it));
    if (it == NULL)
        return (NULL);
    if (lexem->token == LESS 
         || lexem->token == GREAT 
         || lexem->token == GREAT_GREAT)
        assign_type(RDR, it, false);
    else if (lexem->token == LESS_LESS)
        assign_type(RDR, it, true);
    else if (lexem->token == PIPE)
        assign_type(PPE, it, false);
    else
        assign_type(CMD, it, false);
    it->root = false;
    it->token = lexem->str;
    it->left = NULL;
    it->right = NULL;
    return (it);
}


t_tree *leaf_insert(t_tree *it, t_tree *tree)
{
    /* TODO: create insertion case for lower, greater and equal */
    t_tree *root;

    if (tree == NULL)
        return (it);
    root = tree;

}
