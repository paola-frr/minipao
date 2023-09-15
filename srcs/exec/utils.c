/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 20:52:19 by dsydelny          #+#    #+#             */
/*   Updated: 2023/09/15 03:07:51 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getpipe(char *filename, t_hrdoc *hrdoc)
{
	int	fd;
	int	i;

	fd = -1;
	i = 0;
	while (i < hrdoc[0].size)
	{
		if (!strcmp(filename, hrdoc[i].key))
			return (hrdoc[i].fd[0]);
		i++;
	}
	return (fd);
}

void	openfiles(t_cmd *cmds, t_hrdoc *hrdoc)
{
	int	i;
	int	fd;

	i = 0;
	while (cmds->file[i])
	{
		if (cmds->type[i] == 1)
			fd = open(cmds->file[i], O_CREAT | O_TRUNC | O_WRONLY, 0666);
		else if (cmds->type[i] == 2)
			fd = open(cmds->file[i], O_CREAT | O_APPEND | O_WRONLY, 0666);
		else if (cmds->type[i] == 3)
			fd = open(cmds->file[i], O_RDONLY);
		else if (cmds->type[i] == 4)
			fd = getpipe(cmds->file[i], hrdoc);
		if (fd == -1)
			free_in_fd(cmds);
		if (cmds->type[i] == 1 || cmds->type[i] == 2)
			dup_n_close(fd, STDOUT_FILENO);
		else
			dup_n_close(fd, STDIN_FILENO);
		i++;
	}
}

void	redirection(t_data *data, t_cmd *cmds, int index)
{
	int		fd;

	fd = 0;
	if (index != 0)
		dup_n_close(data->prev_pipe, STDIN_FILENO);
	if (index != data->nbcmd - 1)
		dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[0]);
	close(data->fd[1]);
	openfiles(cmds, data->hrdoc);
}

char	*check_cmd(t_data *data, char ***env, char **tab)
{
	char	*cmd;

	if (!ft_strchr(tab[0], '/'))
	{
		data->path = get_path(*env);
		if (!data->path)
		{
			ft_printf("bash: %s: command not found\n", tab[0]);
			return (NULL);
		}
		cmd = find_path(data, tab[0]);
		if (!cmd)
			return (NULL);
	}
	else
		cmd = ft_strdup(tab[0]);
	return (cmd);
}
