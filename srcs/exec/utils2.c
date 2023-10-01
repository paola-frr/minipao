/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 03:06:46 by dsydelny          #+#    #+#             */
/*   Updated: 2023/10/01 05:20:37 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_data *data, int ac)
{
	data->pid = malloc(sizeof(int) * ac);
	if (!data->pid)
		exit(1);
	data->prev_pipe = -1;
	data->path = NULL;
}

void	manage_cmds(t_data *data, char ***env)
{
	char	*cmd;

	if (builtin(data->cmds->cmd))
		data->exit_code = call_builtin(data->cmds->cmd, data->cmds, env);
	else
	{
		cmd = check_cmd(data, env, data->cmds->arg);
		if (cmd)
			execve(cmd, data->cmds->arg, *env);
		the_perror(data->cmds->cmd);
		free(cmd);
		data->exit_code = 127;
	}
}

void	wait_n_close(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbcmd)
	{
		waitpid(data->pid[i++], &data->exit_code, 0);
		if (WIFEXITED(data->exit_code))
			data->exit_code = WEXITSTATUS(data->exit_code);
	}
	close(data->fd[0]);
	free(data->pid);
}

int	count_len(char **tab)
{
	int	i;

	i = 0;
	int j = 0;
	while (tab && tab[i])
	{

		printf("tab = |%s\n", tab[i]);
		if (strncmp(" <<", tab[i], 3) != 0)
			j++;
		i++;
	}
	return (j);
}

int	is_there_hrdoc(char *str)
{
	int	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
			return (1);
		i++;
	}
	return (0);
}
