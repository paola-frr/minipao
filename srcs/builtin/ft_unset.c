/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 03:18:53 by pferreir          #+#    #+#             */
/*   Updated: 2023/09/14 04:07:44 by pferreir         ###   ########.fr       */
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

int	ft_unset(char **tab, char ***env)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (!tab || strcmp(tab[0], "unset") || !(*env))
		return (0);
	if (tab[1] == NULL)
		return (1);
	while (tab[++i])
	{
		j = -1;
		str = ft_strjoin(tab[i], "=");
		while ((*env)[++j])
		{
			if (!strncmp((*env)[j], str, ft_strlen(str)))
			{
				free(str);
				ft_remove_from_env(strdup((*env)[j]), env);
				break ;
			}
		}
		free (str);
	}
	return (1);
}
