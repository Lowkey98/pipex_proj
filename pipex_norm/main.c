/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 09:04:09 by ayafdel           #+#    #+#             */
/*   Updated: 2021/09/23 18:08:48 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void  ft_exit_errno(char *str)
{
    if (!str)
        printf("Error: %s", strerror(errno));
    else
        printf("Error: %s: %s",strerror(errno),str);
    //printf("a");
    exit(EXIT_FAILURE);
}

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
        free(pathname);
    }
    if (path[i] == 0)
        ft_error_two_msg("zsh: command not found:",cmd);    
    return pathname;
}

void child_command(char *argv,int *pipe_fd, int fd_in, char **envp)
{
    char **cmd;
    char  *path;

    cmd = ft_split(argv,' ');
    path = fetch_pathname(cmd[0],envp);
    close(pipe_fd[0]); //???
    dup2(fd_in,STDIN_FILENO);
    dup2(pipe_fd[1],STDOUT_FILENO);
    if ((execve(path, cmd, envp) == -1))
        printf("error");    
}
void parent_command(char **argv,int *pipe_fd, int fd_out, char **envp)
{
    char **cmd;
    char *path;

    cmd = ft_split(argv[3],' ');
    path  = fetch_pathname(cmd[0],envp);
    close(pipe_fd[1]); //???
    dup2(pipe_fd[0],STDIN_FILENO);
    dup2(fd_out,STDOUT_FILENO);
    if ((execve(path, cmd, envp) == -1))
        printf("error\n"); 
}

t_fd    open_file(char **argv, char argc)
{
    t_fd fd;

    fd.in = open(argv[1],O_RDONLY);
    if (fd.in == -1)
        ft_exit_errno(argv[1]);
    fd.out = open(argv[argc - 1],O_WRONLY | O_CREAT | O_TRUNC | O_RDONLY, 0777 );
    if (fd.out == -1)
        ft_exit_errno(argv[argc - 1]);
    return (fd);  
}

int main(int argc, char **argv,char **envp)
{
    
    t_fd fd;
    int pipe_fd[2];
    int id;

    if (argc != 5)
        ft_error_msg("You need 5 arguments");    
    pipe(pipe_fd);
    fd = open_file(argv, argc);
    id = fork();
    if (id == 0)         
        child_command(argv[2], pipe_fd, fd.in,envp);
    else
        parent_command(argv, pipe_fd, fd.out,envp);
    return (0);
}       