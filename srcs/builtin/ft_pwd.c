/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:19:27 by dsydelny          #+#    #+#             */
/*   Updated: 2023/10/02 04:46:27 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef PATH_MAX
# define PATH_MAX	10000
#endif

int	ft_pwd(void)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	if (path[0])
		return (printf("%s\n", path), 0);
	return (1);
}
