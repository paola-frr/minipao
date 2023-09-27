/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:39:30 by dsydelny          #+#    #+#             */
/*   Updated: 2023/09/27 21:51:49 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	type_of_arr(char *s)
{
	if (!ft_strcmp(">", s))
		return (1);
	else if (!ft_strcmp(">>", s))
		return (2);
	else if (!ft_strcmp("<", s))
		return (3);
	else if (!ft_strcmp("<<", s))
		return (4);
	return (0);
}

void	do_malloc(t_cmd *cmds, int a, int t)
{
	cmds->arg = ft_calloc(sizeof(char *), a + 1);
	if (!cmds->arg)
		return ;
	cmds->file = ft_calloc(sizeof(char *), t + 1);
	if (!cmds->file)
		return ;
	cmds->type = ft_calloc(sizeof(int), t);
	if (!cmds->file)
		return ;
}

void	mallocall(t_cmd	*cmds, char **tab)
{
	int	i;
	int	t;
	int	a;

	i = 0;
	t = 0;
	a = 0;
	while (tab[i])
	{
		if (type_of_arr(tab[i]))
		{
			t++;
			i++;
		}
		else
		{
			a++;
			i++;
		}
	}
	do_malloc(cmds, a, t);
}

t_cmd	*parse(char **tab)
{
	static t_cmd	cmds = {0};
	int				i;
	int				t;
	int				a;

	i = 0;
	t = 0;
	a = 0;
	mallocall(&cmds, tab);
	while (tab[i])
	{
		if (type_of_arr(tab[i]))
		{
			cmds.type[t] = type_of_arr(tab[i]);
			cmds.file[t++] = tab[i + 1];
			i++;
		}
		else
			cmds.arg[a++] = tab[i];
		i++;
	}
	cmds.cmd = cmds.arg[0];
	return (&cmds);
}
