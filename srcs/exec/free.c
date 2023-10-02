/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:42:11 by dsydelny          #+#    #+#             */
/*   Updated: 2023/10/02 06:58:19 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmds)
{
	free(cmds->arg);
	free(cmds->type);
	free(cmds->file);
}

void	free_inchildprocess(t_data *data, t_cmd *cmds, int hd)
{
	if (hd)
		free_cmd(cmds);
	if (data->arg)
		ft_freetab(data->arg);
	if (data->split)
		ft_freetab(data->split);
	if (data->env)
		ft_freetab(data->env);
	if (data->env)
		ft_freetab(data->path);
	if (data->str)
		free(data->str);
	if (!hd)
		free(data->hrdoc);
}

void	free_in_fd(t_cmd *cmds)
{
	free_cmd(cmds);
	fprintf(stderr, "%s\n", strerror(errno));
	exit(1);
}
