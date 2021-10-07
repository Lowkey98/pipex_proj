/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 09:12:02 by ayafdel           #+#    #+#             */
/*   Updated: 2021/10/07 09:28:09 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <string.h>
# include <sys/errno.h>

typedef struct s_fd
{
	int	pipe[2];
	int	in;
	int	out;
}	t_fd;

typedef struct s_arg
{
	char	**v;
	int		c;
	char	**env;
}	t_arg;

char	*read_file(char *filename);
char	*fetch_pathname(char	*cmd, char	**envp);
void	ft_exit_errno(char	*str);

#endif