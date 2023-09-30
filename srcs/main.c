/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 03:41:15 by pferreir          #+#    #+#             */
/*   Updated: 2023/09/30 21:48:28 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data = {0};
	char	*str;
	int		i;

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
		// data.str = str;
		ft_expand(&str, &data.env, data.exit_code);
		if (!str || !*str)
			continue ;
		ft_quote(str);
		if (str)
			data.split = ft_split(str, '|');
		if (is_there_hrdoc(str))
			here_doc(&data, str);
		execution(&data, data.split, &data.env);
		free(str);
		ft_freetab(data.split);
	}
	free(str);
	ft_freetab(data.env);
	// ft_freetab(data.split);
}
