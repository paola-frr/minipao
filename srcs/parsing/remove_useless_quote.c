/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_useless_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 01:27:52 by pferreir          #+#    #+#             */
/*   Updated: 2023/09/01 01:41:57 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_previous_quote(char *str, int i)
{
	int	i1;
	int	count;

	i1 = 0;
	count = 0;
	while (str && i1 < i)
	{
		if (str[i1] == '"' || str[i1] == '\'')
			count++;
		i1++;
	}
	if (count % 2 == 0)
		return (1);
	return (0);
}

int	count_useless_quote(char *str)
{
	int	i;
	int	len;
	int	count;

	i = 0;
	len = ft_strlen(str);
	count = 0;
	while (str && str[i])
	{
		if (i + 2 < len && count_previous_quote(str, i)
			&& (str[i] == '"' || str[i] == '\'') && str[i + 1] == str[i])
				i += 2;
		else if (i + 2 < len && count_previous_quote(str, i)
			&& (str[i] == '"' || str[i] == '\'') && str[i + 2] == str[i])
		{
			count += 1;
			i += 3;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

int	skip_useless_quote(char *str, char *new, int i, int *i1)
{
	int	size;

	size = ft_strlen(str);
	if (i + 1 < size && count_previous_quote(str, i)
		&& (str[i] == '\'' || str[i] == '"') && str[i + 1] == str[i])
		return (2);
	else if (i + 2 < size && count_previous_quote(str, i)
		&& (str[i] == '"' || str[i] == '\'') && str[i + 2] == str[i])
	{
		new[(*i1)++] = -str[i + 1];
		return (3);
	}
	else
	{
		new[(*i1)++] = str[i];
		return (1);
	}
}

char	*remove_useless_quote(char *str)
{
	char	*new;
	int		i;
	int		i1;
	int		len;
	int		size;

	i = 0;
	i1 = 0;
	len = count_useless_quote(str);
	size = ft_strlen(str);
	if (len == size)
		return (str);
	new = malloc(sizeof(char) * (len + 1));
	while (i1 < len && i < size)
		i += skip_useless_quote(str, new, i, &i1);
	new[i1] = '\0';
	if (count_useless_quote(new) != len)
		remove_useless_quote(new);
	return (free(str), new);
}
