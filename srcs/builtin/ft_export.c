/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:22:42 by pferreir          #+#    #+#             */
/*   Updated: 2023/09/12 19:57:27 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_in_env(char *add, char ***env)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (ft_strlen_tab(*env) == 0)
		return (1);
	while (add[i] != '=')
		i++;
	while ((*env)[j])
	{
		if ((*env)[j][i] && !ft_strncmp(add, (*env)[j], i))
		{
			free((*env)[j]);
			(*env)[j] = ft_strdup(add);
			return (0);
		}
		j++;
	}
	return (j);
}

void	ft_add_to_env(char *add, char ***env)
{
	int		i;
	char	**new;
	int		len;

	i = 0;
	len = replace_in_env(add, env);
	if (!len)
		return ;
	new = ft_calloc(len + 2, sizeof(char *));
	if (!new)
		return ;
	while (env && *env && (*env)[i])
	{
		new[i] = ft_strdup((*env)[i]);
		free((*env)[i]);
		i++;
	}
	new[i] = ft_strdup(add);
	free(*env);
	*env = new;
}

int	ft_export(char	**tab, char ***env)
{
	int	i;
	int	j;

	i = 0;
	if (!tab || strcmp(tab[i], "export"))
		return (0);
	if (tab[++i] == NULL)
		return (printf("\n"), 1);
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] && tab[i][j] != '=')
		{
			if ((i == 0 && !ft_isalpha_(tab[i][0])) || (!ft_isalpha_(tab[i][j])
				&& !ft_isdigit(tab[i][j]) && tab[i][j] != '='))
			{
				printf("export: `%s': not a valid identifier\n", tab[i]);
				break ;
			}
			if (tab[i][++j] == '=')
				ft_add_to_env(tab[i], env);
		}
		i++;
	}
	return (1);
}
