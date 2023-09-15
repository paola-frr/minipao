/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:23:12 by dsydelny          #+#    #+#             */
/*   Updated: 2023/09/15 03:08:50 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_process(t_data *data, char **tab, char ***env, int i)
{
	char	**arg;
	char	*cmd;

	free(data->pid);
	data->arg = ft_split(tab[i], ' ');
	ft_unquote(data->arg, env);
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
	manage_cmds(data, env);
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

void	manage_builtin(t_data *data, char ***env)
{
	int		fd[2];

	fd[0] = dup(0);
	fd[1] = dup(1);
	openfiles_builtin(data->cmds);
	call_builtin(data->cmds->cmd, data->cmds, env);
	dup2(fd[0], 0);
	dup2(fd[1], 1);
}

void	main_fork(t_data *data, char **tab, char ***env)
{
	int	i;

	i = 0;
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

void	execution(t_data *data, char **tab, char ***env)
{
	int		i;
	char	*cmd;

	i = 0;
	data->nbcmd = count_len(tab);
	data->arg = ft_split(tab[0], ' ');
	ft_unquote(data->arg, env);
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
		manage_builtin(data, env);
	else
		main_fork(data, tab, env);
}
