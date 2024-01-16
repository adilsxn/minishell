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
    extern void exec_pipe(t_tree *tree, t_env* env);    
    extern void exec_cmd(t_tree *tree, t_env* env);

    it->kind = type;
    if (type == RDR)
        it->fn = exec_rdr;
    else if (type == PPE)
        it->fn = exec_pipe;
    else 
        it->fn = exec_cmd;
    if (hdflag == true)
        it->heredoc = true;
    else
        it->heredoc = false;
}

t_tree *make_leaf(t_lexer *lexem)
{
    t_tree *it;

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
            perror("Error: Parsing");
        tree = tree_insert(tree, it);
        i = i->next;
    }
    tree->root  = true;
    return (tree);
}
