/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 21:09:53 by dsydelny          #+#    #+#             */
/*   Updated: 2023/08/31 19:44:12 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>
// #include <stdlib.h>

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

// int main(int ac, char **av)
// {
// 	char *tab1[5] = {"..", NULL}; // works
// 	char *tab2[5] = {"..", "a", NULL}; // not work
// 	char *tab3[5] = {"ssfd", NULL}; // not work
// 	char *tab4[5] = {NULL}; // works
// 	printf("BEFORE %s\n", getcwd(NULL, 1024));
// 	ft_cd(tab1);
// 	printf("AFTER %s\n", getcwd(NULL, 1024));
// 	// ft_cd(tab2);
// 	// ft_cd(tab3);
// }
