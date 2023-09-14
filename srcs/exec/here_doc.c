/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:45:13 by dsydelny          #+#    #+#             */
/*   Updated: 2023/09/14 22:42:13 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// just add the function signal(SIGINT, &sigint_heredoc)
// at the beggining of your heredoc :)

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

char *key_word(char *s, t_hrdoc *hrdoc)
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
	pid_t	child_pid;
	char	*s;
	int		z;
	int		i;

	data->n_hrdocs = how_many_hrdoc(str);
	hrdoc = ft_calloc(sizeof(t_hrdoc), data->n_hrdocs);
	data->hrdoc = hrdoc;
	z = 0;
	i = 0;
	while (z < data->n_hrdocs)
	{
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
		{
			hrdoc[z].size = data->n_hrdocs;
			pipe(hrdoc[z].fd);
			hrdoc[z++].key = key_word(&str[i + 2], hrdoc);
		}
		i++;
	}
	for (int r = 0; z < data->n_hrdocs; z++)
		fprintf(stderr, "DELIMITER = [%s]\n", hrdoc[z].key);
	child_pid = fork();
	if (child_pid == -1)
		exit(EXIT_FAILURE);
	if (child_pid == 0)
	{
		int c = 0;
		while (c < data->n_hrdocs)
		{
			while (1)
			{
				s = readline(hrdoc[c].key);
				if (!s || !strcmp(s, hrdoc[c].key))
					break ;
				ft_putendl_fd(s, hrdoc[c].fd[1]);
				free(s);
			}
			close(hrdoc[c].fd[1]);
			close(hrdoc[c].fd[0]);
			free(hrdoc[c].key);
			free(s);
			c++;
		}
		free(hrdoc);
		exit(1);
	}
	else if (child_pid > 0)
	{
		for (int c = 0; c < data->n_hrdocs; c++)
			close(hrdoc[c].fd[1]);
	}
	waitpid(child_pid, NULL, 0);
}
