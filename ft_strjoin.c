/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 10:16:17 by ayafdel           #+#    #+#             */
/*   Updated: 2021/07/18 11:11:04 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>

int     ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char		*temp;
	int			i;
	int			j;

	j = 0;
	i = 0;
	while (s2[i] != 0)
		i++;
	if ((temp = malloc(ft_strlen(s1) + i + 1)) == 0)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		temp[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		temp[i] = s2[j];
		i++;
		j++;
	}
	temp[i] = '\0';
	//free(s1);
	return (temp);
}