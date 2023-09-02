/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 00:33:06 by pferreir          #+#    #+#             */
/*   Updated: 2023/09/03 00:31:06 by pferreir         ###   ########.fr       */
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
		if (str && str[i] == DQUOTE || str[i] == SQUOTE)
		{
			c = str[i++];
			bo = 0;
			while (str[i] && str[i] != c)
			{
				str[i] *= -1;
				i++;
			}
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
		if (str[i + 1] && !ft_strncmp(&str[i], "<<", 2)
			|| !ft_strncmp(&str[i],">>", 2))
			i += 1;
		i++;
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (i != c && !str[i])
			return (0);
		if (str[c] == '<' && str[c + 1] && str[i] == '>'
				&& str[i + 1] && str[i + 1] == ' ')
			return (-c);
		if (str[c] != '|' && !ft_strchr("<>|", str[i]))
			return (i + 1);
		else if (str[c] == '|' && !ft_strchr("|", str[i]))
			return (i + 1);
		return (-c);
	}
	return (i + 1);
}

void	print_syntax_error(char *str, int i)
{
	printf("hello\n");
	if (str[i] == '|')
		printf("bash : syntax error near unexpected token `|'\n");
	else if (str[i + 3] && str[i + 3] == '|')
		printf("bash : syntax error near unexpected token `|'\n");
	else if (i == 0 || (str[i + 1] && str[i + 1] == ft_isspace(str[i])))
			printf("bash : syntax error near unexpected token `newline'\n");
	else if (str[i + 1] && (!str[i + 2] || (str[i + 2] && !ft_strchr("<>", str[i + 2]))))
	{
		if (str[i + 1] == '>')
			printf("syntax error near unexpected token `>'\n");
		if (str[i + 1] == '<')
			printf("syntax error near unexpected token `<'\n");
	}
	else if (str[i + 1] && ft_strchr("<>", str[i + 1])
		&& str[i + 2] && ft_strchr("<>", str[i + 2]))
		{
			if (str[i + 1] == '>' && str[i + 2] == '>')
				printf("syntax error near unexpected token `>>'\n");
			if (str[i + 1] == '>' && str[i + 2] == '<')
				printf("syntax error near unexpected token `>'\n");
			if (str[i + 1] == '<' && str[i + 2] == '<')
				printf("syntax error near unexpected token `<<'\n");
			if (str[i + 1] == '<' && str[i + 2] == '>')
				printf("syntax error near unexpected token `<>'\n");
		}
	else
		printf("cas a gerer\n");
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
		i = check_rafter(str, i);
		if (i <= 0)
		{
			if (ft_strlen(str) > (-i -1) && (!ft_strncmp(&str[-i], "<<", 2)
				|| !ft_strncmp(&str[-i],">>", 2) || !ft_strncmp(&str[-i],"<>", 2)))
				i -= 1;
			printf("i = %d\n", i);
			return (print_syntax_error(str, -i), 0);
		}
	}
	return (1);
}

/*

*<*<* = bash: *: ambiguous redirect

si | suivie de > ok 

< entree standard
> sortie standard 
>> pareil mais n'efface pas le fichier au prealable
<< ec cat << EOF
1. Launch cat
3.Send all read to standard input

*/
