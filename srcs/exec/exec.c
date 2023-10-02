/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:23:12 by dsydelny          #+#    #+#             */
/*   Updated: 2023/10/02 13:33:45 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_process(t_data *data, char **tab, char ***env, int i)
{
	free(data->pid);
	data->arg = ft_split_isspace(tab[i]);
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
	signal(SIGINT, &ctrlc);
	signal(SIGQUIT, &antislash);
	redirection(data, data->cmds, i);
	if (!data->cmds->cmd)
	{
		free_inchildprocess(data, data->cmds, 1);
		exit (1);
	}
	manage_cmds(data, env);
	free_inchildprocess(data, data->cmds, 1);
	exit(data->exit_code);
}

void	parent_process(t_data *data)
{
	close(data->fd[1]);
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
	data->prev_pipe = data->fd[0];
	signal(SIGQUIT, SIG_IGN);
}

// void	manage_builtin(t_data *data, char ***env)
// {
// 	data->new_fd[0] = dup(0);
// 	data->new_fd[1] = dup(1);
// 	openfiles_builtin(data->cmds);
// 	call_builtin(data->cmds->cmd, data->cmds, env);
// 	free_cmd(data->cmds);
// 	dup2(data->new_fd[0], 0);
// 	dup2(data->new_fd[1], 1);
// 	close(data->new_fd[0]);
// 	close(data->new_fd[1]);
// }

void	manage_builtin(t_data *data, char ***env)
{
	int		fd[2];

	fd[0] = dup(0);
	fd[1] = dup(1);
	openfiles_builtin(data->cmds);
	call_builtin(data->cmds->cmd, data->cmds, env);
	free_cmd(data->cmds);
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}

void	main_fork(t_data *data, char **tab, char ***env)
{
	int	i;

	i = 0;
	free_cmd(data->cmds);
	ft_freetab(data->arg);
	init(data, data->nbcmd);
	while (i < data->nbcmd)
	{
		pipe(data->fd);
		signal(SIGINT, SIG_IGN);
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			child_process(data, tab, env, i);
		else if (data->pid[i] > 0)
			parent_process(data);
		i++;
	}
	wait_n_close(data);
	signal(SIGINT, &ctrlc);
}

void	execution(t_data *data, char **tab, char ***env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->nbcmd = count_len(tab);
	if (!data->nbcmd)
		return ;
	data->arg = ft_split_isspace(tab[0]);
	if (!data->arg)
		exit(1);
	while (data->arg[j])
	{
		data->arg[j] = ft_unquote2(data->arg[j]);
		j++;
	}
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
		manage_builtin(data, env);
		ft_freetab(data->arg);
	}
	else
		main_fork(data, tab, env);
}
