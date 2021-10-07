/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_errno.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 09:19:41 by ayafdel           #+#    #+#             */
/*   Updated: 2021/10/07 09:36:22 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "pipex.h"

void	ft_exit_errno(char	*str)
{
	if (!str)
		printf("Error: %s", strerror(errno));
	else
		printf("Error: %s: %s", strerror(errno), str);
	exit(EXIT_FAILURE);
}
