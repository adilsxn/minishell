/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sgnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:07:25 by matde-je          #+#    #+#             */
/*   Updated: 2024/01/16 16:39:12 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//extern t_state g_state;

// void	sigint_handler(int sig)
// {
//     rl_replace_line("", 0);
//     rl_redisplay();
//     rl_done = 1;
//     return ;
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// 	(void) sig;
// }

// void	sigquit_handler(int sig)
// {
// 	ft_putstr_fd("Quit: ", STDERR_FILENO);
// 	ft_putnbr_fd(sig, STDERR_FILENO);
// 	ft_putchar_fd('\n', STDERR_FILENO);
// }

// void	init_signals(void)
// {
// 	rl_event_hook = 0;
// 	signal(SIGINT, sigint_handler);
// 	signal(SIGQUIT, SIG_IGN);
// }


void	setup_sgnl(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void	restore_sgnl(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

void	ignore_sgnl(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void	quit_sgnl(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

void	ignore_sgnl_child(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
}

void	quit_sgnl_child(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

void	ignore_sgnl_parent(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_DFL);
}

void	quit_sgnl_parent(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

