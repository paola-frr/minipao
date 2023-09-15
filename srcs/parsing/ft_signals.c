/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:37:27 by pferreir          #+#    #+#             */
/*   Updated: 2023/09/15 03:18:49 by dsydelny         ###   ########.fr       */
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

void	allsignals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sigint);
}

static void	sigint_heredoc(int signum)
{
	close(STDIN_FILENO);
	write(STDOUT_FILENO, "> ^C\n", 5);
}
