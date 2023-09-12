/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:17:03 by pferreir          #+#    #+#             */
/*   Updated: 2023/09/12 19:58:21 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_space(char *str)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
		}
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

char	*ft_space(char *str)
{
	char	*new;
	char	*tmp;
	int		i;
	char	c;

	tmp = str;
	i = 0;
	new = ft_calloc(count_space(str) + 1, 1);
	if (!new)
		return (NULL);
	while (str && *str)
	{
		if (*str == '\'' || *str == '"')
		{
			new[i++] = *str;
			c = *str++;
			while (*str && *str != c)
				new[i++] = *str++;
			new[i++] = *str++;
		}
		else if (ft_strchr("<>", *str))
		{
			new[i++] = ' ';
			while (*str && ft_strchr("<>", *str))
				new[i++] = *str++;
			new[i++] = ' ';
		}
		else if (ft_strchr("|", *str))
		{
			new[i++] = ' ';
			while (*str && ft_strchr("|", *str))
				new[i++] = *str++;
			new[i++] = ' ';
		}
		else
			new[i++] = *str++;
	}
	return (free(tmp), new);
}