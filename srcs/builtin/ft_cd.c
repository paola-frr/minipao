/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 21:09:53 by dsydelny          #+#    #+#             */
/*   Updated: 2023/10/02 10:13:13 by pferreir         ###   ########.fr       */
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

	i = 1;
	if (!tab)
		return (0);
	if (!ft_strncmp(tab[0], "cd", 2) && tab[i] == NULL)
		go_home();
	else if (!ft_strncmp(tab[0], "cd", 2) && tab[i] && tab[i + 1] == NULL)
	{
		r = chdir(tab[i]);
		if (r)
		{
			ft_printf("bash: cd: %s: No such file or directory\n", tab[i]);
			return (data->exit_code = 1, 1);
		}
	}
	else if (!ft_strncmp(tab[0], "cd", 2) && tab[i] && tab[i + 1])
	{
		ft_printf("bash: cd: too many arguments\n");
		data->exit_code = 1;
		return (1);
	}
	return (0);
}
