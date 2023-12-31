/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:35:41 by pferreir          #+#    #+#             */
/*   Updated: 2023/10/02 05:06:38 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_echo_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && (str[i + 1] != '\0' && str[i + 1] == 'n'))
	{
		while (str && str[++i])
		{
			if (str[i] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}

int	ft_echo(char **tab)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (!tab[i])
		return (printf("\n"), 0);
	if (check_echo_option(tab[i]))
		option = 1;
	while (tab[i] && check_echo_option(tab[i]))
		i++;
	while (tab && tab[i])
	{
		printf("%s", tab[i]);
		if (tab[i + 1])
			printf(" ");
		i++;
	}
	if (!option)
		printf("\n");
	return (0);
}
