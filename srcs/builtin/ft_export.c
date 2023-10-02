/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:22:42 by pferreir          #+#    #+#             */
/*   Updated: 2023/10/02 10:29:12 by pferreir         ###   ########.fr       */
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

int	ft_add_to_env(char *add, char ***env)
{
	int		i;
	char	**new;
	int		len;

	i = 0;
	len = replace_in_env(add, env);
	if (!len)
		return (-1);
	new = ft_calloc(len + 2, sizeof(char *));
	if (!new)
		return (0);
	while (env && *env && (*env)[i])
	{
		new[i] = ft_strdup((*env)[i]);
		free((*env)[i]);
		i++;
	}
	new[i] = ft_strdup(add);
	free(*env);
	*env = new;
	return (-1);
}

int	ft_export_check(char	**tab)
{
	if (!tab || ft_strcmp(tab[0], "export"))
		return (0);
	if (tab[1] == NULL)
		return (printf("\n"), 1);
	return (-1);
}

int	ft_export(char	**t, char ***env, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (ft_export_check(t) > 0)
		return (ft_export_check(t));
	while (t[++i])
	{
		j = 0;
		while (t[i][j])
		{
			if ((j == 0 && !ft_isalpha_(t[i][0])) ||
				(j != 0 && !(ft_isalpha_(t[i][j]))) || ft_isdigit(t[i][j]))
			{
				ft_printf("export: `%s': not a valid identifier\n", t[i]);
				data->exit_code = 1;
			}
			if (t[i][++j] == '=')
				j = ft_add_to_env(t[i], env);
			if (data->exit_code == 1 || j == -1)
				break ;
		}
	}
	return (0);
}
