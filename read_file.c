/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 09:23:27 by ayafdel           #+#    #+#             */
/*   Updated: 2021/07/19 10:33:20 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
char *read_file(char *filename)
{
    char *file;
    int fd;
    char *buff;

    file = malloc(1);
    file = "\0";
    fd = open(filename,O_RDONLY);
    buff = malloc(4);
    while (read(fd,buff,1))
    {
        file = ft_strjoin(file,buff);
    }
    //read(fd,buff,10);
    //free(buff);
    return (file);
}