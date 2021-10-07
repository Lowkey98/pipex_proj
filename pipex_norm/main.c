/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 09:31:34 by ayafdel           #+#    #+#             */
/*   Updated: 2021/10/07 09:35:26 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_command(char *argv, int *pipe_fd, int fd_in, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = fetch_pathname(cmd[0], envp);
	close(pipe_fd[0]);
	dup2(fd_in, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	if ((execve(path, cmd, envp) == -1))
	{
		free(path);
		ft_exit_errno(0);
	}
}

void	parent_command(char **argv, int *pipe_fd, int fd_out, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv[3], ' ');
	path = fetch_pathname(cmd[0], envp);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	if ((execve(path, cmd, envp) == -1))
	{
		free(path);
		ft_free_split(cmd);
		ft_exit_errno(0);
	}
}

t_fd	open_file(char **argv, char argc)
{
	t_fd	fd;

	fd.in = open(argv[1], O_RDONLY);
	if (fd.in == -1)
		ft_exit_errno(argv[1]);
	fd.out = open(argv[argc - 1], O_WRONLY | O_CREAT | \
	 O_TRUNC | O_RDONLY, 0777);
	if (fd.out == -1)
		ft_exit_errno(argv[argc - 1]);
	return (fd);
}

void	check_arg(char **argv, int argc)
{
	int	i;

	i = 2;
	if (argc != 5)
		ft_error_msg("You need 5 arguments");
	if (argv[1][0] == '\0' || argv[argc - 1][0] == '\0')
		ft_error_msg("zsh: no such file or directory: ");
	while (i < argc - 1)
	{
		if (argv[i][0] == '\0')
			ft_error_msg("zsh: permission denied: ");
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_fd	fd;
	int		pipe_fd[2];
	int		id;

	check_arg(argv, argc);
	pipe(pipe_fd);
	fd = open_file(argv, argc);
	id = fork();
	if (id == 0)
		child_command(argv[2], pipe_fd, fd.in, envp);
	else
		parent_command(argv, pipe_fd, fd.out, envp);
	return (0);
}
