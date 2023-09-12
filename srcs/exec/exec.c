/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:23:12 by dsydelny          #+#    #+#             */
/*   Updated: 2023/09/12 01:06:38 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_data *data, int ac, char **tab)
{
	data->pid = malloc(sizeof(int) * ac);
	if (!data->pid)
		exit(1);
	data->prev_pipe = -1;
	data->path = NULL;
}

int	child_process(t_data *data, char **tab, char **env, int i)
{
	char	**arg;
	char	*cmd;

	free(data->pid);
	data->arg = ft_split(tab[i], ' ');
	if (!data->arg)
		exit(1);
	if (!*data->arg)
	{
		ft_printf("bash: : command not found\n");
		return (free(data->arg), exit(1), 1);
	}
	data->cmds = parse(data->arg);
	data->cmds->data = data;
	redirection(data, data->cmds, i); 
	if (!data->cmds->cmd)
	{
		free_inchildprocess(data, data->cmds);
		exit (1);
	}
	if (builtin(data->cmds->cmd))
		call_builtin (data->cmds->cmd, data->cmds, env);
	else
	{
		cmd = check_cmd(data, env, data->cmds->arg);
		if (cmd)
			execve(cmd, data->cmds->arg, env);
		the_perror(data->cmds->cmd);
		free(cmd);
	}
	free_inchildprocess(data, data->cmds);
	exit(127);
}

void	parent_process(t_data *data)
{
	close(data->fd[1]);
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
	data->prev_pipe = data->fd[0];
}

void	wait_n_close(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbcmd)
		waitpid(data->pid[i++], 0, 0);
	close(data->fd[0]);
	free(data->pid);
}

int	count_len(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

void	print_tab(char **tab)
{
	for (int i = 0; tab[i]; i++)
	{
		printf("[%i]{%s}\n", i, tab[i]);
	}
}

int    ft_strlen_tab(char **tab)
{
    int    i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}

void	execution(t_data *data, char **tab, char **env)
{
	int	i;
	char *cmd;
	
	i = 0;
	printf("[[[[[[[%s]]]]]]]\n", tab[0]);
	data->nbcmd = count_len(tab);
	data->arg = ft_split(tab[0], ' ');
	if (!data->arg)
		exit(1);
	if (!*data->arg)
	{
		ft_printf("bash: : command not found\n");
		free(data->arg);
		exit(1);
	}
	data->cmds = parse(data->arg);
	data->cmds->data = data;
	if (data->nbcmd == 1 && builtin(data->cmds->cmd))
	{
		int fd[2];
		fd[0] = dup(0);
		fd[1] = dup(1);
		printf("i am builtin %s\n", data->cmds->cmd);
		openfiles_builtin(data->cmds);
		call_builtin(data->cmds->cmd, data->cmds, env);
		dup2(fd[0], 0);
		dup2(fd[1], 1);
	}
	else
	{
		free_cmd(data->cmds);
		ft_freetab(data->arg);
		init(data, data->nbcmd, tab);
		while (i < data->nbcmd)
		{
			pipe(data->fd);
			data->pid[i] = fork();
			if (data->pid[i] == 0)
				child_process(data, tab, env, i);
			else if (data->pid[i] > 0)
				parent_process(data);
			i++;
		}
		wait_n_close(data);
	}
}
