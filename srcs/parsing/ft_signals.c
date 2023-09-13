/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:37:27 by pferreir          #+#    #+#             */
/*   Updated: 2023/09/14 00:49:58 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint(int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	allsignals()
{
	signal(SIGQUIT, SIG_IGN);
	signal(EOF, SIG_DFL);
	signal(SIGINT, &sigint);
}


static void	sigint_heredoc(int signum)
{
	(void)signum;
	close(STDIN_FILENO);
	write(STDOUT_FILENO, "> ^C\n", 5);
}