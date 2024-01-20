/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:03:18 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/05 23:03:18 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

static void rdir_o(t_tree *tree)
{
    int fd_o;

    fd_o = open(tree->left->token, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        if (fd_o == -1)
            perror("Error while opening outfile\n");
    dup2(fd_o, STDOUT_FILENO);
    close(fd_o);
}

static void rdir_i(t_tree *tree)
{
    int fd_i;

    fd_i = open(tree->left->token, O_RDONLY);
        if (fd_i == -1)
            perror("Error while opening outfile\n");
    dup2(fd_i, STDIN_FILENO);
    close(fd_i);
}

static void appnd(t_tree *tree)
{
    int fd_a;

    fd_a = open(tree->left->token, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
    if (fd_a == -1)
        perror("Error while appending outfile\n");
    dup2(fd_a, STDOUT_FILENO);
    close(fd_a);
}

static void hdoc(t_tree *tree, t_env *env)
{
    int fd_hd;
    char *input;

    (void)env;
    fd_hd = open(".tmp_hd", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    if (fd_hd == -1)
        perror("Error on hdoc\n");
    while (true)
    {
        input = readline("heredoc> ");
        if (!input || !ft_strncmp(input, tree->left->token, FOPEN_MAX))
            break ;
        expander(env, input);
    }
    free(input);
    close(fd_hd);
    fd_hd = open(".tmp_hd", O_RDONLY, S_IRWXU);
    if (fd_hd == -1)
        perror("Error on hdoc\n");
    dup2(fd_hd, STDIN_FILENO);
    close(fd_hd);
}

void exec_rdr(t_tree *tree, t_env *env)
{
    if (ft_strequ(tree->token, ">"))
        rdir_o(tree);
    else if (ft_strequ(tree->token, "<"))
        rdir_i(tree);
    else if (ft_strequ(tree->token, ">>"))
       appnd(tree);
    if (ft_strequ(tree->token, ">"))
        hdoc(tree, env);
}
