/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_pathname.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 10:13:37 by ayafdel           #+#    #+#             */
/*   Updated: 2021/10/07 10:13:46 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*fetch_env_path(char	**envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (envp[i] == 0)
		ft_error_two_msg("Error:", "Path not found");
	return (envp[i]);
}

char	*fetch_pathname(char *cmd, char	**envp)
{
	char	**path;
	char	*pathname;
	int		i;

	i = 0;
	path = ft_split(fetch_env_path(envp), ':');
	path[0] = ft_free_first(path[0], ft_strdup(ft_strrchr(path[0], '=') + 1));
	while (path[i])
	{
		pathname = ft_free_first(path[i], ft_strjoin_char(path[i], cmd, '/'));
		if (access(pathname, F_OK) == 0)
			break ;
		i++;
	//if (!pathname)
		free(pathname);
	}
	if (path[i] == 0)
		ft_error_two_msg("zsh: command not found:", cmd);
	return (pathname);
}
