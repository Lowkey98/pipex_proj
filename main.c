/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 09:31:34 by ayafdel           #+#    #+#             */
/*   Updated: 2021/10/10 15:42:28 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_command(char *argv, int *pipe_fd, char *file, char **envp)
{
	char	**cmd;
	char	*path;
	int		fd;

	cmd = ft_split(argv, ' ');
	//print_strings(cmd);
	path = fetch_pathname(cmd[0], envp);
	//printf("hello\n");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_exit_errno(file);
	close(pipe_fd[0]);
	dup2(fd, STDIN_FILENO);
	 close(fd);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	if ((execve(path, cmd, envp) == -1))
	{
		free(path);
		ft_exit_errno(0);
	}
}

void	second_command(char **argv, int *pipe_fd, char *file, char **envp)
{
	char	**cmd;
	char	*path;
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC | O_RDONLY, 0777);
	if (fd == -1)
		ft_exit_errno(file);
	cmd = ft_split(argv[3], ' ');
	path = fetch_pathname(cmd[0], envp);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if ((execve(path, cmd, envp) == -1))
	{
		free(path);
		ft_free_split(cmd);
		ft_exit_errno(0);
	}
}

// void	check_arg(char **argv, int argc)
// {
// 	int	i;

// 	i = 2;
// 	if (argc != 5)
// 		ft_error_msg("You need 5 arguments");
// 	// if (argv[1][0] == '\0' || argv[argc - 1][0] == '\0')
// 	// 	ft_error_msg("zsh: no such file or directory: ");
// 	// // while (i < argc - 1)
// 	// {
// 	// 	if (argv[i][0] == '\0')
// 	// 		ft_error_msg("zsh: permission denied: ");
// 	// 	i++;
// 	// }
// }

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		id[2];
	int		status;

	if (argc != 5)
		ft_error_msg("You need 5 arguments");
	//check_arg(argv, argc);
	pipe(pipe_fd);
	id[0] = fork();
	if (id[0] == 0)
		first_command(argv[2], pipe_fd, argv[1], envp);
	else
	{		
		id[1] = fork();
		if (id[1] == 0)
			second_command(argv, pipe_fd, argv[4], envp);
		else
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			waitpid(id[0], &status, 0);
			waitpid(id[1], &status, 0);
		}
	}
	return (WEXITSTATUS(status));
}