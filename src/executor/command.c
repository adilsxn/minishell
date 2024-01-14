/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:10:04 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/11 13:10:04 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

static exec_bi(t_tree *tree, t_env *env);
static exec_bin(t_tree *tree, t_env *env)
{
    pid_t pid;
    int sts;
    char *cmdpath;
    char **argv;

    cmdpath = cmd_finder(tree, env);
    argv = build_av(tree);
    pid = fork();
    if (pid == -1)
        ft_putstr_fd("Error: fork failed\n", 2);
    else if (pid == 0)
    {
        if (execve(cmdpath, argv, NULL) == -1)
            ft_putstr_fd("Error: execve failed\n", 2);
    }
    else
    {
        waitpid(pid, &sts, 0);
        if (WIFEXITED(sts))
            printf("Child %d exited with code %d\n", pid, WEXITSTATUS(sts));
    }   
}

void exec_cmd(t_tree *tree, t_env *env)
{
    int status;
    char *cmd;
    char **argv;

    if (builtin) //builtin
        exec_bi(tree, env);
    else
        exec_bin(tree, env);
    
}