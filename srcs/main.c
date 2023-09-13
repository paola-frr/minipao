/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 03:41:15 by pferreir          #+#    #+#             */
/*   Updated: 2023/09/14 00:32:56 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data = {0};
	char	*str;
	int		i;
	char	**monenv;
	char	**tab;
	t_cmd *cmds;

	(void)ac;
	(void)av;
	i = 0;
	data.env = ft_copy(env);
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
		str = ft_space(str);
		printf("[%s]\n", str);
		ft_expand(&str, &monenv);
		printf("[[%s]]\n", str);
		if (!check_quote(str))
		{
			free(str);
			printf("quote error\n");
			continue ;
		}
		if (!str)
			return (0);
		if (!ft_syntax(str))
		{
			free(str);
			continue ;
		}
		if (str)
			data.split = ft_split(str, '|');
		// here_doc(&data, str);
		execution(&data, data.split, &env);
		free(str);
		ft_freetab(data.split);
	}
	free(str);
	ft_freetab(data.env);
	// ft_freetab(data.split);
}
