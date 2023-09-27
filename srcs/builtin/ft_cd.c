/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 21:09:53 by dsydelny          #+#    #+#             */
/*   Updated: 2023/09/27 20:15:40 by dsydelny         ###   ########.fr       */
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

int	ft_cd(char **tab, t_data *data)
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
			fprintf(stderr, "bash: cd: %s: No such file or directory\n", tab[i]);
			data->exit_code = 1;
			return (1);
		}
	}
	else if (!strncmp(tab[0], "cd", 2) && tab[i] && tab[i + 1])
	{
		fprintf(stderr, "bash: cd: too many arguments\n");
		data->exit_code = 1;
		return (1);
	}
	return (0);
}
