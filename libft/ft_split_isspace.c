/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_isspace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:24:08 by pferreir          #+#    #+#             */
/*   Updated: 2023/08/05 02:15:12 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strdup_isspace(char *str)
{
	char	*mot;
	int		i;
	int		taille_mot;

	taille_mot = 0;
	i = 0;
	while (str[taille_mot] != '\0' && !ft_isspace(str[taille_mot]))
		taille_mot++;
	mot = ft_calloc((taille_mot + 1), sizeof(char));
	if (mot == NULL)
		return (NULL);
	while (str[i] != '\0' && !ft_isspace(str[i]))
	{
		mot[i] = str[i];
		i++;
	}
	return (mot);
}

static int	count_words_isspace(char *str)
{
	int	nb_mot;
	int	i;

	nb_mot = 0;
	i = 0;
	while (str && str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			str++;
		if (str[i])
			nb_mot++;
		while (str[i] && !ft_isspace(str[i]))
			str++;
	}
	return (nb_mot);
}

char	**do_split_isspace(char *str, int nb)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_calloc(nb + 1, sizeof(char *));
	if (tab == NULL)
		return (NULL);
	while (str && *str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (*str)
		{
			tab[i] = ft_strdup_isspace(str);
			if (tab[i] == NULL)
				return (ft_freetab(tab), NULL);
			i++;
		}
		while (*str && !ft_isspace(*str))
			str++;
	}
	return (tab);
}

char	**ft_split_isspace(char *str)
{
	int	i;
	int	nb;

	i = 0;
	if (!str || !str[i])
		return (NULL);
	nb = count_words_isspace(str);
	if (!nb)
		return (NULL);
	return (do_split_isspace(str, nb));
}
