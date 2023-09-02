/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 03:09:08 by pferreir          #+#    #+#             */
/*   Updated: 2023/09/01 00:47:56 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_replace(char **str, int start, char *replace)
{
	char	*new;
	int		i;
	int		j;
	int		len_replace;
	int		end;

	i = -1;
	j = 0;
	len_replace = ft_strlen(replace);
	end = start + 1;
	while ((*str)[end] && (ft_isalpha_((*str)[end]) || ft_isdigit((*str)[end])))
		end++;
	new = malloc(ft_strlen(*str) - end + start + len_replace + 2);
	while (++i < start)
		new[i] = (*str)[i];
	while (replace && replace[j])
		new[i++] = replace[j++];
	while ((*str)[end])
		new[i++] = (*str)[end++];
	new[i] = '\0';
	free(*str);
	*str = new;
	return (free(replace), len_replace + start - 2);
}

int	skip_simple_quote(char *str, int i)
{
	int	i1;
	int	bo;

	i1 = 0;
	bo = 0;
	while (i1 < i && str[i1])
	{
		if (str[i1] && str[i1] == '"')
		{
			bo = 1;
			while (i1 < i && str[++i1] != '"')
				;
			if (i1 < i && str[i1] == '"')
			{
				i1++;
				bo = 0;
			}
		}
		else
			i1++;
	}
	if (str[i] && str[i] == '\'' && bo == 0)
		while (str[++i] != '\'')
			;
	return (i);
}

int	remove_expand(char **str, int start)
{
	char	*new;
	int		i;
	int		e;

	i = 0;
	e = start + 1;
	if ((*str)[e] && ft_isalpha_((*str)[e]))
	{
		while ((*str)[e] && (ft_isalpha_((*str)[e]) || ft_isdigit((*str)[e])))
			e++;
	}
	else
		e++;
	new = malloc(sizeof(char) * (ft_strlen(*str) - e + start + 2));
	while (*str && (*str)[i] && i < start)
	{
		new[i] = (*str)[i];
		i++;
	}
	while ((*str)[e])
		new[i++] = (*str)[e++];
	new[e] = '\0';
	free(*str);
	*str = new;
	return (start);
}

int	expand_is_in_env(char *str, int start, char ***env, char **replace)
{
	int		i;
	int		end;
	int		len;
	char	*value;
	char	*check;

	i = 0;
	end = start;
	while (str[end] && (ft_isalpha_(str[end]) || ft_isdigit(str[end])))
		end++;
	end--;
	check = ft_substr(str, start, end - start + 1);
	len = ft_strlen(check);
	while ((*env)[i])
	{
		value = return_value((*env)[i]);
		if (!ft_strcmp(check, value))
		{
			*replace = ft_substr((*env)[i], len + 1, ft_strlen((*env)[i]));
			return (free(check), free(value), 1);
		}
		free(value);
		i++;
	}
	return (free(check), 0);
}

int	ft_expand(char	**str, char ***env)
{
	int		i;
	int		start;
	char	*replace;

	i = 0;
	if (!str && !(*str))
		return (0);
	while ((*str)[i])
	{
		i = skip_simple_quote(*str, i);
		if ((*str)[i] && (*str)[i] == '$')
		{
			start = i++;
			if ((*str)[i] && (*str)[i] == '?')
				i = printf("on remplace par le dernier exit status\n");
			else if ((*str)[i] && ft_isalpha_((*str)[i])
				&& expand_is_in_env(*str, start + 1, env, &replace))
				i = expand_replace(str, start, replace) - 1;
			else
				i = remove_expand(str, start);
		}
		else
			i++;
	}
	return (1);
}
