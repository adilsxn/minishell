/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:07:25 by matde-je          #+#    #+#             */
/*   Updated: 2024/01/23 12:54:58 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void ignore_the_sigquit(void)
{
    struct sigaction event;

    ft_bzero(&event, sizeof(struct sigaction));
    event.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &event, NULL);
}

void sig_hdoc_child(int sig)
{
    if (sig == SIGINT)
    {
        // clean_fds();
        ft_putchar_fd('\n', 1);
        exit(SIGINT);
    }
}

void sig_hdoc_parent(int sig)
{
    (void)sig;
    // rl_replace_line("", 0);
    // rl_on_new_line();
    // clean_fds();
    rl_redisplay();
}

void	sig_new_prompt(int sig)
{
    if (sig == SIGINT)
    {
        ft_putchar_fd('\n', 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void	signal_handler(void (*handler)(int), int signal)
{
	struct sigaction	event;

    ignore_the_sigquit();
    ft_bzero(&event, sizeof(struct sigaction));
	event.sa_handler = handler;
    event.sa_flags = SA_SIGINFO | SA_RESTART;
    sigemptyset(&event.sa_mask);
	sigaction(signal, &event, NULL);
}


