/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 09:44:40 by ayafdel           #+#    #+#             */
/*   Updated: 2021/10/07 09:45:53 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
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
	int	tmp;
}	t_fd;

typedef struct s_arg
{
	char	**v;
	int		c;
	char	**env;
}	t_arg;

char	*fetch_pathname(char *cmd, char	**envp);
#endif