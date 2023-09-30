/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 00:45:08 by pferreir          #+#    #+#             */
/*   Updated: 2023/10/01 01:06:40 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dquote_expand(char **str, int e)
{
	int		i;
	char	c;
	char	d;

	i = 0;
	d = 0;
	while (i < e)
	{
		if ((*str)[i] == '\'' || (*str)[i] == '"')
		{
			if ((*str)[i] == '"')
				d = 1;
			c = (*str)[i++];
			while ((*str)[i] && (*str)[i] != c)
				i++;
			i++;
			if (i >= e)
				return (-1);
		}
		i++;
	}
	return (e + 1);
}

int	skip_quote(char *str, int i)
{
	char	c;

	if (str[i] && (str[i] == '\'' || str[i] == '"'))
	{
		c = str[i++];
		while (str[i] != c)
			i++;
	}
	if (i >= (int)ft_strlen(str))
		return (ft_strlen(str) - 1);
	return (i);
}

int	expand_delimit(char *str, int start)
{
	int	i;

	i = start - 1;
	while (i > 0 && ft_isspace(str[i]))
		i--;
	if (i > 0 && !ft_strncmp(&str[i - 1], "<<", 2))
		return (1);
	return (0);
}

int	end_of_expand(char **str, int start)
{
	int	e;

	e = start + 1;
	if (expand_delimit(*str, start))
		return (-1);
	else if ((*str)[e] == '?')
		return (e + 1);
	else if (!(*str)[e] || (*str)[e] == 32 || (*str)[e] == 33
		|| ((*str)[e] >= 35 && (*str)[e] <= 38) || ((*str)[e] >= 40
		&& (*str)[e] <= 47) || ((*str)[e] >= 58 && (*str)[e] <= 64)
		|| ((*str)[e] >= 91 && (*str)[e] <= 96) || (*str)[e] == 123
		|| (*str)[e] == 125)
		return (-1);
	else if ((*str)[e] == '?' || ft_isdigit((*str)[e]))
		return (e + 1);
	else if ((*str)[e] && ft_isalpha_((*str)[e]))
		while ((*str)[e] && (ft_isalpha_((*str)[e]) || ft_isdigit((*str)[e])))
			e++;
	return (e);
}
