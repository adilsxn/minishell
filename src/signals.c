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

static void	sig_new_prompt(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	ign_sigquit(void)
{
	struct sigaction	event;

	ft_bzero(&event, sizeof(struct sigaction));
	event.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &event, NULL);
}

void	sig_handl(void)
{
	struct sigaction	event;

	ign_sigquit();
	ft_bzero(&event, sizeof(struct sigaction));
	event.sa_handler = &sig_new_prompt;
	sigaction(SIGINT, &event, NULL);
}
