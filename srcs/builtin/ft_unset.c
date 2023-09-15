/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 03:18:53 by pferreir          #+#    #+#             */
/*   Updated: 2023/09/16 00:00:54 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_remove_from_env(char *remove, char ***env)
{
	int		i;
	int		j;
	char	**new;
	int		len;

	i = 0;
	j = 0;
	new = ft_calloc(ft_strlen_tab(*env), sizeof(char *));
	if (!new)
		return ;
	while (env && (*env) && (*env)[i])
	{
		if (strcmp((*env)[i], remove))
			new[j++] = ft_strdup((*env)[i]);
		free((*env)[i]);
		i++;
	}
	free(*env);
	*env = new;
	free(remove);
}

int	ft_unset_check(char	**tab, char ***env)
{
	if (!tab || strcmp(tab[0], "unset") || !(*env))
		return (0);
	if (tab[1] == NULL)
		return (printf("\n"), 1);
	return (-1);
}

int	ft_unset(char **tab, char ***env)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (ft_unset_check(tab, env) > 0)
		return (ft_unset_check(tab, env));
	while (tab[++i])
	{
		j = -1;
		str = ft_strjoin(tab[i], "=");
		while ((*env)[++j])
		{
			if (!strncmp((*env)[j], str, ft_strlen(str)))
			{
				ft_remove_from_env(strdup((*env)[j]), env);
				break ;
			}
		}
		free(str);
	}
	return (1);
}
