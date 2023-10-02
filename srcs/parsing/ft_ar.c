/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 21:10:33 by pferreir          #+#    #+#             */
/*   Updated: 2023/10/02 06:34:42 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_isspace(char *str, int i)
{
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

int	ft_ar(char *str)
{
	int		i;
	char	c;

	i = -1;
	while (str && str[++i])
	{
		i = skip_quote(str, i);
		if (ft_strchr("<>", str[i]))
		{
			c = str[i++];
			if (str[i] && ft_strchr("<>", c) && ft_strchr("<>", str[i]))
				i++;
			i = skip_isspace(str, i);
			if (!str[i] || ft_strchr("<>|", str[i]))
				return (printf("bash: ambiguous redirect\n"), 1);
		}
		if (ft_strchr("|", str[i]))
		{
			i++;
			i = skip_isspace(str, i);
			if (!str[i] || ft_strchr("|", str[i]))
				return (printf(SYNTAXERROR), 1);
		}
	}
	return (0);
}
