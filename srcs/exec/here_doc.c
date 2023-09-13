/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:45:13 by dsydelny          #+#    #+#             */
/*   Updated: 2023/09/13 02:09:33 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	how_many_hrdoc(char *str)
{
	int i;
	int	hrdoc;
	
	i = 0;
	hrdoc = 0;
	while(str[i])
	{
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
			hrdoc++;
		i++;	
	}
	return (hrdoc);
}

char *key_word(char *s)
{
	int	i;
	int	j;
	char *key;

	i = 0;
	j = 0;
	while (s && s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	while (s && s[i] && s[i] != ' ' && s[i] != '\t')
	{
		i++;
		j++;
	}
	key = ft_calloc(sizeof(char), j + 1);
	if (!key)
		return (NULL);
	i = 0;
	j = 0;
	while (s && s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	while (s && s[i] && s[i] != ' ' && s[i] != '\t')
		key[j++] = s[i++];
	return (key);
}

void	here_doc(t_data *data, char *str)
{
	t_hrdoc	*hrdoc;
	
	data->n_hrdocs = how_many_hrdoc(str);
	hrdoc = ft_calloc(sizeof(t_hrdoc), data->n_hrdocs);
	int z = 0;
	int i = 0;
	printf("nb docs: %d\n", data->n_hrdocs);
	while (z < data->n_hrdocs)
	{
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
		{
			hrdoc[z++].key = key_word(&str[i + 2]);
			printf("keyword: [%s]\n", hrdoc[z - 1].key);
		}
		i++;
	}
	// filling delimiters;
	// make a function that prints everything
	// fork blabla LATEr
}

void	letsgo_hrdoc(t_data *data, char *s)
{
	char *str;

	 str = readline("heredoc >");
}
