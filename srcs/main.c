/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 03:41:15 by pferreir          #+#    #+#             */
/*   Updated: 2023/09/15 23:22:12 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data = {0};
	char	*str;
	int		i;
	char	**tab;
	t_cmd *cmds;

	(void)ac;
	(void)av;
	i = 0;
	data.env = ft_copy(env);
	allsignals();
	while (1)
	{
		str = readline("pao> ");
		if (!str)
			break ;
		if (!*str)
		{
			free(str);
			continue ;
		}
		add_history(str);
		 if (syntax(&data, str) == 1)
		 	continue ;
		if (syntax(&data, str) == 2)
			break ;
		str = ft_space(str);
		ft_expand(&str, &data.env, data.exit_code);
		ft_quote(str);
		if (str)
			data.split = ft_split(str, '|');
		here_doc(&data, str);
		execution(&data, data.split, &data.env);
		free(str);
		ft_freetab(data.split);
	}
	free(str);
	ft_freetab(data.env);
	// ft_freetab(data.split);
}
