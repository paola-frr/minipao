/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:17:03 by pferreir          #+#    #+#             */
/*   Updated: 2023/10/01 00:46:55 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_space2(char *str, int i)
{
	int	c;

	c = str[i++];
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	count_space(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = count_space2(str, i) + 1;
		else if (ft_strchr("<>", str[i]))
		{
			count += 2;
			while (str[i] && ft_strchr("<>", str[i]))
				i++;
		}
		else if (ft_strchr("|", str[i]))
		{
			count += 2;
			while (str[i] && ft_strchr("|", str[i]))
				i++;
		}
		else
			i++;
	}
	return (count + i);
}

int	ft_space2(char *str, int i, int *j, char *new)
{
	if (ft_strchr("<>", str[*j]))
	{
		new[i++] = ' ';
		while (str[*j] && ft_strchr("<>", str[*j]))
			new[i++] = str[(*j)++];
		new[i++] = ' ';
	}
	else if (ft_strchr("|", str[*j]))
	{
		new[i++] = ' ';
		while (str[*j] && ft_strchr("|", str[*j]))
			new[i++] = str[(*j)++];
		new[i++] = ' ';
	}
	else
		new[i++] = str[(*j)++];
	return (i);
}

char	*ft_space(char *str)
{
	char	*new;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	new = ft_calloc(count_space(str) + 1, 1);
	if (!new)
		return (NULL);
	while (str && str[j])
	{
		if (str[j] == '\'' || str[j] == '"')
		{
			new[i++] = str[j];
			c = str[j++];
			while (str[j] && str[j] != c)
				new[i++] = str[j++];
			new[i++] = str[j++];
		}
		else
			i = ft_space2(str, i, &j, new);
	}
	return (free(str), new);
}
