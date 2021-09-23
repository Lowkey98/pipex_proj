/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 09:04:09 by ayafdel           #+#    #+#             */
/*   Updated: 2021/09/23 12:59:03 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


char *fetch_env_path(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i],"PATH=",5) == 0)
            break;
        i++;
    }
    return envp[i];
}
char *fetch_pathname(char *cmd, char**envp)
{
    char **path;
    //char *tmp;
    char *pathname;
    int i;

    i = 0;
    path = ft_split(fetch_env_path(envp),':');
    path[0] = ft_free_first(path[0],ft_strdup(ft_strrchr(path[0], '=') + 1));
    
    while (path[i])
    {
        pathname = ft_free_first(path[i],ft_strjoin_char(path[i],cmd,'/'));
        if (access(pathname,F_OK) == 0)
            break;
        i++;
        //free(pathname);
    }
    return pathname;
}

void child_command(char **argv,int *pipe_fd, int fd_in, char **envp)
{
    char **cmd;
    
    cmd = ft_split(argv[2],' ');
    close(pipe_fd[0]); //???
    dup2(fd_in,STDIN_FILENO);
    dup2(pipe_fd[1],STDOUT_FILENO);
    if ((execve(fetch_pathname(cmd[0],envp), cmd, envp) == -1))
        printf("error");    
}
void parent_command(char **argv,int *pipe_fd, int fd_out, char **envp)
{
    char **cmd;
    
    cmd = ft_split(argv[3],' ');
    close(pipe_fd[1]); //???
    dup2(pipe_fd[0],STDIN_FILENO);
    dup2(fd_out,STDOUT_FILENO);      
    if ((execve(fetch_pathname(cmd[0],envp), cmd, envp) == -1))
        printf("error\n"); 
}
int main(int argc, char **argv,char **envp)
{
    
    int fd_in;
    int fd_out;
    int pipe_fd[2];
    int id;

    if (argc == 5)
    {
        pipe(pipe_fd);
        fd_in = open(argv[1],O_RDONLY);
        fd_out = open(argv[4],O_WRONLY | O_CREAT | O_TRUNC | O_RDONLY,0777);
        if (fd_in == -1)
            printf("error open");
        id = fork();
        if (id == 0)         
            child_command(argv, pipe_fd, fd_in,envp);
        else
            parent_command(argv, pipe_fd, fd_out,envp);
    }
    return (0);
}       