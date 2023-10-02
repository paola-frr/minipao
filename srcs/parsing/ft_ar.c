/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 21:10:33 by pferreir          #+#    #+#             */
/*   Updated: 2023/10/02 02:36:17 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	ft_ar2(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
		}
		if (str[i + 1] && ft_strchr("|", str[i]))
		{
			c = str[i++];
			while (str[i] && ft_isspace(str[i]))
				i++;
			if (!str[i] || ft_strchr("<>|", str[i]))
			{
				printf("bash : syntax error near unexpected token `newline'\n");
				return (free(str), 1);
			}
		}
		i++;
	}
	return (0);
}*/

/*int	ft_ar(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
		}
		if (str[i + 1] && ft_strchr("<>", str[i]))
		{
			c = str[i++];
			if (str[i] && ft_strchr("<>", c) && ft_strchr("<>", str[i]))
				i++;
			while (str[i] && ft_isspace(str[i]))
				i++;
			if (!str[i] || ft_strchr("<>|", str[i]))
				return (printf("bash: ambiguous redirect\n"), free(str), 1);
		}
		i++;
	}
	//return (ft_ar2(str));
	return (0);
}*/

int	ft_ar(char *str)
{
	int		i;
	char	c;

	i = 0;
	while(str && str[i])
	{
		i = skip_quote(str, i);
		if (ft_strchr("<>", str[i]))
		{
			c = str[i++];
			if (str[i] && ft_strchr("<>", c) && ft_strchr("<>", str[i]))
				i++;
			while (str[i] && ft_isspace(str[i]))
				i++;
			if (!str[i] || ft_strchr("<>|", str[i]))
				return (printf("bash: ambiguous redirect\n"), free(str), 1);
		}
		if (ft_strchr("|", str[i]))
		{
			i++;
			while (str[i] && ft_isspace(str[i]))
				i++;
			if (!str[i] || ft_strchr("|", str[i]))
				return (printf(SYNTAXERROR), free(str), 1);
		}
		i++;
	}
	return (0);
}
