/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:24:27 by dsydelny          #+#    #+#             */
/*   Updated: 2023/09/11 20:17:12 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(char *str)
{
	if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "pwd")
	|| !ft_strcmp(str, "export") ||!ft_strcmp(str, "unset")
	||!ft_strcmp(str, "exit") || !ft_strcmp(str, "echo")
	|| !ft_strcmp(str, "env"))
		return (1);
	return (0);
}

int	call_builtin(char *str, t_cmd *cmds, char **env)
{
	if (!ft_strcmp(str, "cd"))
		return (ft_cd(cmds->arg), 1);
	else if (!ft_strcmp(str, "pwd"))
		return (ft_pwd(cmds->arg), 1);
	else if (!ft_strcmp(str, "export"))
		return (ft_export(cmds->arg, &env), 1);
	else if (!ft_strcmp(str, "unset"))
		return (ft_unset(cmds->arg, &env), 1);
	else if (!ft_strcmp(str, "exit"))
		return (ft_exit(cmds->arg, cmds->data, cmds), 1);
	else if (!ft_strcmp(str, "echo"))
		return (ft_echo(cmds->arg), 1);
	else if (!ft_strcmp(str, "env"))
		return (ft_env(env), 1);
	else
		return (0);
	free_inchildprocess(cmds->data, cmds);
}
