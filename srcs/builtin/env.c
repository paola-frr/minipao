/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:57:23 by pferreir          #+#    #+#             */
/*   Updated: 2023/09/27 18:43:45 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_copy(char **env)
{
	int		n;
	int		i;
	char	**cpenv;

	n = 0;
	i = 0;
	while (env && env[n])
		n++;
	cpenv = ft_calloc(n + 1, sizeof(char *));
	if (!cpenv)
		return (NULL);
	while (i < n)
	{
		cpenv[i] = ft_strdup(env[i]);
		i++;
	}
	return (cpenv);
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	if (!env || !(*env))
		return (0);
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (1);
}

char	*return_value(char *str)
{
	int		i;
	int		end;
	char	*new;

	i = 0;
	end = 0;
	if (!str)
		return (NULL);
	while (str[end] != '=')
		end++;
	new = malloc(sizeof(char) * (end + 1));
	if (!new)
		return (NULL);
	while (i < end)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
