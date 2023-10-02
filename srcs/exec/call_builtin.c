/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:24:27 by dsydelny          #+#    #+#             */
/*   Updated: 2023/10/02 10:14:25 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "pwd")
		|| !ft_strcmp(str, "export") ||!ft_strcmp(str, "unset")
		||!ft_strcmp(str, "exit") || !ft_strcmp(str, "echo")
		|| !ft_strcmp(str, "env"))
		return (1);
	return (0);
}

int	call_builtin(char *str, t_cmd *cmds, char ***env)
{
	if (!ft_strcmp(str, "cd"))
		return (ft_cd(cmds->arg, cmds->data));
	else if (!ft_strcmp(str, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(str, "export"))
		return (ft_export(cmds->arg, env, cmds->data));
	else if (!ft_strcmp(str, "unset"))
		return (ft_unset(cmds->arg, env));
	else if (!ft_strcmp(str, "exit"))
		return (ft_exit(cmds->arg, cmds->data, cmds));
	else if (!ft_strcmp(str, "echo"))
		return (ft_echo(cmds->arg));
	else if (!ft_strcmp(str, "env"))
		return (ft_env(*env));
	else
		return (0);
}

int	openfiles_builtin(t_cmd *cmds)
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
		if (fd == -1)
		{
			cmds->data->exit_code = 1;
			ft_printf("%s\n", strerror(errno));
			return (1);
		}
		if (cmds->type[i] == 1 || cmds->type[i] == 2)
			dup_n_close(fd, STDOUT_FILENO);
		else
			dup_n_close(fd, STDIN_FILENO);
		i++;
	}
	return (0);
}
