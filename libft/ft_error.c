/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:12:18 by ayafdel           #+#    #+#             */
/*   Updated: 2021/10/06 13:15:01 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error_msg(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	ft_error_two_msg(char *str_one, char *str_two)
{
	printf("%s %s\n", str_one, str_two);
	exit(EXIT_FAILURE);
}
