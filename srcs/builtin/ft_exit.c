/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 00:01:49 by dsydelny          #+#    #+#             */
/*   Updated: 2023/10/02 04:46:05 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	num_required(const char *nptr, t_data *data, t_cmd *cmds)
{
	fprintf(stderr, "exit\nbash: exit: %s: numeric argument required\n", nptr);
	free_inchildprocess(data, cmds, 1);
	data->exit_code = 2;
	exit (2);
}

long long int	ft_long_atoi(const char *nptr, t_data *data, t_cmd *cmds)
{
	unsigned long long int	n;
	int						i;
	int						signe;

	n = 0;
	i = 0;
	signe = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-' )
	{
		if (nptr[i] == '-')
			signe *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		n = 10 * n + nptr[i] - '0';
		if ((n > LLONG_MAX) || (n > LLONG_MAX && signe == -1))
			num_required(nptr, data, cmds);
		i++;
	}
	if (!ft_isdigit(nptr[i]) && nptr[i] != '\0')
		n = 0;
	return ((long long)n * signe);
}

void	two_arg_exit(char **tab, t_data *data, t_cmd *cmds, int i)
{
	long long int	num;

	num = ft_long_atoi(tab[i + 1], data, cmds);
	if (num == 0)
	{
		printf("exit\n");
		fprintf(stderr, "exit: %s: numeric argument required\n", tab[i + 1]);
		free_inchildprocess(data, cmds, 1);
		data->exit_code = 2;
		exit (2);
	}
	else if (num <= 9223372036854775807)
	{
		printf("exit\n");
		free_inchildprocess(data, cmds, 1);
		data->exit_code = (unsigned char) num;
		exit((unsigned char) num);
	}
}

void	three_arg_exit(char **tab, t_data *data, t_cmd *cmds, int i)
{
	long long int	num;

	num = ft_long_atoi(tab[i + 1], data, cmds);
	if (num == 0)
	{
		printf("exit\n");
		printf("exit\n");
		fprintf(stderr, "exit: %s: numeric argument required\n", tab[i + 1]);
		free_inchildprocess(data, cmds, 1);
		data->exit_code = 2;
		exit (2);
	}
	else if (num <= 9223372036854775807)
	{
		data->exit_code = 1;
		printf("exit\n");
		fprintf(stderr, "bash: exit: too many arguments\n");
	}
}

int	ft_exit(char **tab, t_data *data, t_cmd *cmds)
{
	int				i;

	i = 0;
	if (!tab)
		return (0);
	if (!strncmp(tab[i], "exit", 4) && !tab[i + 1])
	{
		printf("exit\n");
		free_inchildprocess(data, cmds, 1);
		data->exit_code = 0;
		exit (0);
	}
	else if ((!strncmp(tab[i], "exit", 4) && tab[i + 1] && !tab[i + 2]))
		two_arg_exit(tab, data, cmds, i);
	else if ((!strncmp(tab[i], "exit", 4) && tab[i + 1] && tab[i + 2]))
		three_arg_exit(tab, data, cmds, i);
	return (0);
}
