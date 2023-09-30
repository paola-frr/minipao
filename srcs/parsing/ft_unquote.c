/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 02:53:43 by pferreir          #+#    #+#             */
/*   Updated: 2023/09/30 20:47:40 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quote(char *str)
{
	int		i;
	char	c;

	i = -1;
	while (str && str[++i])
	{
		if (str && (str[i] == '"' || str[i] == '\''))
		{
			c = str[i++];
			while (str[i] && str[i] != c)
			{
				str[i] *= -1;
				i++;
			}
		}
	}
}

char	*ft_unquote_str(char *str, int len, int *start, char c)
{
	int		k;
	int		i;
	char	*new;

	k = 0;
	i = 0;
	new = malloc(sizeof(char) * len);
	if (!new)
		return (0);
	while (i < *start)
		new[k++] = str[i++];
	i++;
	while (k < len && str[i] != c)
	{
		str[i] *= -1;
		new[k++] = str[i++];
	}
	if (str[i] == c)
		*start = i - 1;
	i++;
	while (k < len && str[i])
		new[k++] = str[i++];
	new[k] = '\0';
	free (str);
	return (new);
}

void	ft_unquote(char **tab, char ***env)
{
	int		i;
	int		j;
	int		len;
	char	c;

	(void)env;
	j = 0;
	while (tab && tab[j])
	{
		i = 0;
		len = ft_strlen(tab[j]);
		while (tab[j][i])
		{
			if (tab[j][i] == '\'' || tab[j][i] == '"')
			{
				c = tab[j][i];
				tab[j] = ft_unquote_str(tab[j], len, &i, c);
			}
			else
				i++;
		}
		j++;
	}
}
