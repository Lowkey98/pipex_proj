/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_errno.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 09:19:41 by ayafdel           #+#    #+#             */
/*   Updated: 2021/10/10 08:07:37 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "pipex.h"

void	ft_exit_errno(char	*str)
{
	if (str)
		perror(str);
	else
		perror("");
	exit(EXIT_FAILURE);
}
