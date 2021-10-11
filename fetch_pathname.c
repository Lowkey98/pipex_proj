/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_pathname.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 09:03:37 by ayafdel           #+#    #+#             */
/*   Updated: 2021/10/11 12:38:44 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*fetch_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (envp[i]);
}

void	error_command(void)
{
	ft_putstr_fd(" : command not found\n", 2);
	exit(127);
}

void	ft_perror(char *cmd)
{
	perror(cmd);
	exit(127);
}

char	*fetch_pathname(char	*cmd,	char	**envp)
{
	char	**path;
	char	*pathname;
	int		i;

	i = 0;
	if (!cmd)
		error_command();
	if (access(cmd, F_OK) == 0 && cmd[0] == '/')
		return (ft_strdup(cmd));
	path = ft_split(fetch_env_path(envp), ':');
	path[0] = ft_free_first(path[0], ft_strdup(ft_strrchr(path[0], '=') + 1));
	while (path[i])
	{
		pathname = ft_strjoin_char(path[i], cmd, '/');
		if (access(pathname, F_OK) == 0)
			break ;
		i++;
		free(pathname);
		if (path[i] == 0)
			error_command();
	}
	ft_free_split(path);
	return (pathname);
}
