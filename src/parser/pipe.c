/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:12:32 by matilde           #+#    #+#             */
/*   Updated: 2024/01/08 19:10:15 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>

static pid_t out_proc(t_tree *tree, t_env *env, int fd[2])
{
    /*TODO: add signal handler*/
    pid_t pid;

    pid = fork();
    if (pid == -1)
        printf("error: spawning the out process\n");
    if (pid == 0)
    {
        /*TODO: add signal handler*/
        close(fd[0]);
        if (dup2(fd[1], STDOUT_FILENO) == -1)
            printf("error\n");
        close(fd[1]);
        tree->f(tree, env);
        exit(0);
    }
    return (pid);
}

static pid_t in_proc(t_tree *tree, t_env *env, int fd[2])
{
    /*TODO: add signal handler*/
    pid_t pid;

    pid = fork();
    if (pid == -1)
        printf("error: spawning the in process\n");
    if (pid == 0)
    {
        /*TODO: add signal handler*/
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) == -1)
            printf("error\n");
        close(fd[0]);
        tree->f(tree, env);
        exit(0);
    }
    return (pid);
}

void exec_pipe(t_tree *tree, t_env *env)
{
    int fd[2];
    pid_t child[2];

    if (pipe(fd) == -1)
        printf("Error: while opening pipes");
    child[0] = out_proc(tree, env, fd);
    waitpid(child[0], NULL, 0);
    close(fd[1]);
    child[1] = in_proc(tree, env, fd);
    waitpid(child[1], NULL, 0);
    close(fd[0]);
    /*TODO: Add signal handler for projects*/
}
