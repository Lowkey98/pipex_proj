#include "pipex_bonus.h"



// void dp_free(char **str)
// {
//     int i;

//     i = 0;
//     while (str)
// }



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
    if (envp[i] == 0)
        ft_error_two_msg("Error:","Path not found");
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
    //if (!pathname)
        free(pathname);
    }
    if (path[i] == 0)
        ft_error_two_msg("zsh: command not found:",cmd);
    return pathname;
}


void  ft_exit_errno(char *str)
{
    if (!str)
        printf("Error: %s", strerror(errno));
    else
        printf("Error: %s: %s",strerror(errno),str);
    //printf("a");
    exit(EXIT_FAILURE);
}

void child_command(t_arg arg, t_fd fd, int cmd_index)
{
    char **cmd;
    char *path;

    cmd = ft_split(arg.v[cmd_index],' ');
    path = fetch_pathname(cmd[0],arg.env);
    close(fd.pipe[0]); //???
    dup2(fd.tmp,STDIN_FILENO);
    close(fd.tmp);
    if (cmd_index + 1 < arg.c - 1)
        dup2(fd.pipe[1],STDOUT_FILENO);
    else
        dup2(fd.out,STDOUT_FILENO);
    close(fd.pipe[1]);
    if ((execve(path, cmd, arg.env) == -1))
    {
        free(path);
        ft_free_split(cmd);
        ft_exit_errno(0);
    }
}

t_arg   fetch_arg(char **argv, int argc, char **envp)
{
    t_arg arg;

    int i;

    i = 2;
 
    if (argv[1][0] == '\0' || argv[argc - 1][0] == '\0')
        ft_error_msg("zsh: no such file or directory: ");
    while (i< argc - 1)
    {
        if (argv[i][0] == '\0')
            ft_error_msg("zsh: permission denied: ");
        i++;
    }
    arg.v = argv;
    arg.c = argc;
    arg.env = envp;
    return (arg);
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
    fd.tmp = fd.in;
    return (fd);  
}

int main(int argc, char **argv,char **envp)
{
    t_fd fd;
    t_arg arg;
    int id;
    int cmd_index = 2;

    arg = fetch_arg(argv, argc, envp);
    if (arg.c == 1)
        return (0);
    fd = open_file(arg.v, arg.c);
    while (cmd_index + 1 < argc)
    {
        if (pipe(fd.pipe) == -1)
            ft_exit_errno(0);
        id = fork();
        if (id == -1)
            ft_exit_errno(0);
        if (id == 0)
            child_command(arg,fd, cmd_index);
        fd.tmp = fd.pipe[0];    
        close(fd.pipe[1]);
        cmd_index++;
    }
    return (0);
}