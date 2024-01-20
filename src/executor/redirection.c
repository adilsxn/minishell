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

void rdir_o(t_tree *tree, t_env *env)
{
    int fd_o;

    (void)env;
    fd_o = open(tree->left->token, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    if (dup2(fd_o, STDOUT_FILENO) == -1)
        perror("Error: duplicating the fd ->");
    close(fd_o);
    if (tree->right != NULL)
        tree->right->fn(tree->right, env);
}

void rdir_i(t_tree *tree, t_env *env)
{
    int fd_i;

    fd_i = open(tree->left->token, O_RDONLY);
    if (fd_i == -1)
    {
        set_env(&env, "?", "1");
        perror("Error: while opening inffile ->");
        return ;
    }
    if (dup2(fd_i, STDIN_FILENO) == -1)
        perror("Error: duplicating the fd ->");
    close(fd_i);
    if (tree->right != NULL)
        tree->right->fn(tree->right, env);
}

void appnd(t_tree *tree, t_env *env)
{
    int fd_a;

    (void)env;
    fd_a = open(tree->left->token, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
    if (dup2(fd_a, STDOUT_FILENO) == -1)
        perror("Error: duplicating the fd ->");
    close(fd_a);
    if (tree->right != NULL)
        tree->right->fn(tree->right, env);
}

bool handle_hd(char **input, t_env *env, t_tree *tree)
{
    if (*input == NULL)
    {
        ft_putendl_fd(HD_W, 2);
        ft_putendl_fd(tree->left->token, 2);
    }
    if (ft_strequ(tree->left->token, *input))
        return (true);
    if (ft_strchr(*input, '$'))
        expander(env, *input);
}
void hdoc(t_tree *tree, t_env *env)
{
    int fd_hd;
    char *input;

    (void)env;
    fd_hd = open(".tmp_hd", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    if (fd_hd == -1)
        perror("Error on opening hdoc ->");
    while (true)
    {
        input = readline("heredoc> ");
        if (!input || !ft_strncmp(input, tree->left->token, FOPEN_MAX))
            break ;
        //expander(env, input);
        ft_putendl_fd(input, fd_hd);
    }
    free(input);
    close(fd_hd);
    fd_hd = open(".tmp_hd", O_RDONLY, S_IRWXU);
    if (fd_hd == -1)
        perror("Error on opening hdoc ->");
    close(fd_hd);
    if (tree->right != NULL)
        tree->right->fn(tree->right, env);
    unlink(".tmp_hd");
}

