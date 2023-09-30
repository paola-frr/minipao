/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:45:13 by dsydelny          #+#    #+#             */
/*   Updated: 2023/09/30 22:13:52 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	how_many_hrdoc(char *str)
{
	int	i;
	int	hrdoc;

	i = 0;
	hrdoc = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
			hrdoc++;
		i++;
	}
	return (hrdoc);
}

char	*key_word(char *s)
{
	int		i;
	int		j;
	char	*key;

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

void	letsgo_child(t_data *data, t_hrdoc *hrdoc)
{
	int		c;
	char	*s;

	c = 0;
	while (c < data->n_hrdocs)
	{
		while (1)
		{
			// signal(SIGINT, &sigint_heredoc);
			s = readline("> ");
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
	ft_freetab(data->arg);
	ft_freetab(data->split);
	ft_freetab(data->env);
	ft_freetab(data->path);
	// free(data->str);
	free(hrdoc);
	exit(1);
}

void	we_do_fork(t_data *data, t_hrdoc *hrdoc)
{
	pid_t	child_pid;
	int		i;

	child_pid = fork();
	if (child_pid == -1)
		exit(EXIT_FAILURE);
	if (child_pid == 0)
	{
		letsgo_child(data, hrdoc);
		// free_inchildprocess(data, data->cmds);
	}
	else if (child_pid > 0)
	{
		i = 0;
		while (i < data->n_hrdocs)
		{
			close(hrdoc[i].fd[1]);
			i++;
		}
	}
	waitpid(child_pid, NULL, 0);
}

void	here_doc(t_data *data, char *str)
{
	int		z;
	int		i;

	data->n_hrdocs = how_many_hrdoc(str);
	data->hrdoc = ft_calloc(sizeof(t_hrdoc), data->n_hrdocs + 1);
	if (!data->hrdoc)
		return ;
	z = 0;
	i = 0;
	while (z < data->n_hrdocs)
	{
		data->hrdoc[z].key = 0;
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
		{
			data->hrdoc[z].size = data->n_hrdocs;
			pipe(data->hrdoc[z].fd);
			data->hrdoc[z++].key = key_word(&str[i + 2]);
		}	
		i++;
	}
	we_do_fork(data, data->hrdoc);
}
