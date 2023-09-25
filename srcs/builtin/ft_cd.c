/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 21:09:53 by dsydelny          #+#    #+#             */
/*   Updated: 2023/09/24 23:14:20 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (home)
		return (chdir(home), 0);
	return (printf("bash: cd: HOME not set\n"), 1);
}

int	ft_cd(char **tab)
{
	int		i;
	int		r;
	char	*home;

	i = 1;
	if (!tab)
		return (0);
	if (!strncmp(tab[0], "cd", 2) && tab[i] == NULL)
		go_home();
	else if (!strncmp(tab[0], "cd", 2) && tab[i] && tab[i + 1] == NULL)
	{
		r = chdir(tab[i]);
		if (r)
		{
			printf("bash: cd: %s: No such file or directory\n", tab[i]);
			return (1);
		}
	}
	else if (!strncmp(tab[0], "cd", 2) && tab[i] && tab[i + 1])
	{
		printf("bash: cd: too many arguments\n");
		return (1);
	}
	return (0);
}
