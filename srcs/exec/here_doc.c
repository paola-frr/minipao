/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:45:13 by dsydelny          #+#    #+#             */
/*   Updated: 2023/10/02 12:12:21 by pferreir         ###   ########.fr       */
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

t_data	*starton(void)
{
	static t_data	data;

	return (&data);
}

static void	exit_hd(int sig)
{
	t_data	*data;
	int		i;

	data = starton();
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		i = -1;
		while (++i < data->n_hrdocs)
		{
			close(data->hrdoc[i].fd[1]);
			close(data->hrdoc[i].fd[0]);
			if (data->hrdoc[i].key != NULL)
				free(data->hrdoc[i].key);
		}
		free_inchildprocess(data, data->cmds, 0);
		exit(130);
	}
}



void	letsgo_child(t_data *data, t_hrdoc *hrdoc)
{
	int		c;
	char	*s;

	c = 0;
	signal(SIGINT, &exit_hd);
	while (c < data->n_hrdocs)
	{
		while (1)
		{
			s = readline("> ");
			ft_expand(&s, &data->env, data->exit_code, 0);
			if (!s || !ft_strcmp(s, hrdoc[c].key))
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
	free_inchildprocess(data, data->cmds, 0);
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
		letsgo_child(data, hrdoc);
	else if (child_pid > 0)
	{
		i = 0;
		while (i < data->n_hrdocs)
		{
			close(hrdoc[i].fd[1]);
			i++;
		}
	}
	signal(SIGINT, &ctrlc);
	waitpid(child_pid, NULL, 0);
}

void	here_doc(t_data *data, char *str)
{
	int	z;
	int	i;

	data->n_hrdocs = how_many_hrdoc(str);
	data->hrdoc = ft_calloc(sizeof(t_hrdoc), data->n_hrdocs + 1);
	if (!data->hrdoc)
		return ;
	z = 0;
	i = 0;
	while (z < data->n_hrdocs)
	{
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
		{
			data->hrdoc[z].size = data->n_hrdocs;
			pipe(data->hrdoc[z].fd);
			data->hrdoc[z++].key = ft_unquote2(key_word(&str[i + 2]));
		}
		i++;
	}
	signal(SIGINT, SIG_IGN);
	we_do_fork(data, data->hrdoc);
}
