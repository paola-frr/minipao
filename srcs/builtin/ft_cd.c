/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 21:09:53 by dsydelny          #+#    #+#             */
/*   Updated: 2023/09/12 21:55:37 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **tab)
{
	int	i;
	int	r;

	i = 1;
	if (!tab)
		return (0);
	if (!strncmp(tab[0], "cd", 2) && tab[i] == NULL)
	{
		printf("why blyat??\n");
		char *home = getenv("HOME");
		if (home)
			return (chdir(home), 0);
		return (printf("bash: cd: HOME not set\n"), 1);
	}
	else if (!strncmp(tab[0], "cd", 2) && tab[i] && tab[i + 1] == NULL)
	{
		r = chdir(tab[i]);
		if (r)
		{
			printf("i came??\n");
			printf("bash: cd: %s: No such file or directory\n", tab[i]);
			return (1);
		}
		printf("suka why? %d\n", r);
	}
	else if (!strncmp(tab[0], "cd", 2) && tab[i] && tab[i + 1])
	{
		printf("why? %s\n", tab[i]);
		printf("bash: cd: too many arguments\n");
		return (1);
	}
	return (0);
}
