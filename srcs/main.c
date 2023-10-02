/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 03:41:15 by pferreir          #+#    #+#             */
/*   Updated: 2023/10/02 13:15:33 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_hrdoc(t_data *data)
{
	int	i;

	i = -1;
	while (i++ < data->n_hrdocs)
		free(data->hrdoc[i].key);
	free(data->hrdoc);
}

void	main_process(t_data *data, char **str)
{
	if (is_there_hrdoc(*str))
		here_doc(data, *str);
	execution(data, data->split, &data->env);
	if (is_there_hrdoc(*str))
		free_hrdoc(data);
	ft_freetab(data->split);
	free(*str);
}

int	idk(t_data *data, char **str)
{
	if (!data->str)
		return (1);
	if (!*data->str)
	{
		ft_printf("bash: : command not found\n");
		return (free(data->str), 1);
	}
	if (ft_ar(data->str))
		return (free(data->str), 1);
	ft_quote(*str);
	if (*str)
		data->split = ft_split(*str, '|');
	if (!data->split)
		return (1);
	return (0);
}

void	the_end(t_data *data, char **str)
{
	free(*str);
	ft_freetab(data->env);
	printf("exit\n");
	rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = starton();
	ft_memset(data, 0, sizeof(t_data));
	data->env = ft_copy(env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc);
	while (1)
	{
		data->str = readline("pao> ");
		add_history(data->str);
		if (syntax(data, data->str) == 1)
			continue ;
		if (syntax(data, data->str) == 2)
			break ;
		data->str = ft_space(data->str);
		ft_expand(&data->str, &data->env, data->exit_code, 1);
		if (idk(data, &data->str))
			continue ;
		main_process(data, &data->str);
	}
	the_end(data, &data->str);
}
