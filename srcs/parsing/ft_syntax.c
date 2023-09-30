/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 00:33:06 by pferreir          #+#    #+#             */
/*   Updated: 2023/09/30 20:47:27 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *str)
{
	int		i;
	int		bo;
	char	c;

	i = -1;
	bo = 1;
	while (str && str[++i])
	{
		if (str && (str[i] == '"' || str[i] == '\''))
		{
			c = str[i++];
			bo = 0;
			while (str[i] && str[i] != c)
				i++;
			if (!str[i])
				return (bo);
			if (str[i] == c)
				bo = 1;
		}
	}
	return (bo);
}

int	check_rafter(char *str, int i)
{
	int	c;

	c = i;
	if (str[i] && ft_strchr("|<>", str[i]))
	{
		if (str[i + 1] && (!ft_strncmp(&str[i], "<<", 2)
			|| !ft_strncmp(&str[i], ">>", 2)))
			i += 1;
		i++;
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (i != c && !str[i])
			return (0);
		if (str[c] == '<' && str[c + 1] && str[i] == '>')
			return (c + 1);
		if (str[c] != '|' && !ft_strchr("<>|", str[i]))
			return (i + 1);
		else if (str[c] == '|' && !ft_strchr("|", str[i]))
			return (c + 1);
		return (-i);
	}
	return (i + 1);
}

void	print_syntax_error(char *str, int i)
{
	int	len;

	len = ft_strlen(str);
	if (str[i] == '|')
		printf("bash : syntax error near unexpected token `|'\n");
	else if (len > i + 3 && str[i + 3] == '|')
		printf("bash : syntax error near unexpected token `|'\n");
	else if (i == 0 || (len > i + 1 && str[i + 1] == ft_isspace(str[i])))
		printf("bash : syntax error near unexpected token `newline'\n");
	else if (str[i] == '>')
	{
		if (len > i + 1 && str[i + 1] == '>')
			printf("bash : syntax error near unexpected token `>>'\n");
		else
			printf("bash : syntax error near unexpected token `>'\n");
	}
	else if (str[i] == '<')
	{
		if (len > i + 1 && str[i + 1] == '<')
			printf("bash : syntax error near unexpected token `<<'\n");
		else if (len > i + 1 && str[i + 1] == '>')
			printf("bash : syntax error near unexpected token `<>'\n");
		else
			printf("bash : syntax error near unexpected token `<'\n");
	}
}

int	ft_syntax(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	if (str && str[i] == '|')
		return (print_syntax_error(str, i), 0);
	while (str[i])
	{
		i = skip_quote(str, i);
		i = check_rafter(str, i);
		if (i <= 0)
			return (print_syntax_error(str, -i), 0);
	}
	return (1);
}

int	syntax(t_data *data, char *str)
{
	if (!*str)
		return (1);
	if (!ft_syntax(str) || !check_quote(str))
	{
		data->exit_code = 0;
		return (1);
	}
	if (!ft_strcmp(str, "exit"))
	{
		data->exit_code = 0;
		return (2);
	}
	return (0);
}
