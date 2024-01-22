/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sgnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:07:25 by matde-je          #+#    #+#             */
/*   Updated: 2024/01/20 12:19:14 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static void sig_new_prompt(int sig)
{
    (void)sig;
    ft_putchar_fd('\n', 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

static void ign_sigquit(void)
{
    struct sigaction event;

    ft_bzero(&event, sizeof(event));
    event.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &event, NULL);
}

void sig_handl(void)
{
    struct sigaction event;

    ign_sigquit();
    ft_bzero(&event, sizeof(event));
    event.sa_handler = &sig_new_prompt;
    sigaction(SIGINT, &event, NULL);
}
