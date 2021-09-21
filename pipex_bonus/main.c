#include "pipex_bonus.h"

char *free_first(char *first, char *str)
{
    free(first);   
    return str;
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
    path[0] = free_first(path[0],ft_strdup(ft_strrchr(path[0], '=') + 1));
    
    while (path[i])
    {
        pathname = free_first(path[i],ft_strjoin_char(path[i],cmd,'/'));
        if (access(pathname,F_OK) == 0)
            break;
        i++;
        free(pathname);
    }
    return pathname;
}

void child_command(t_arg arg, t_fd fd, int cmd_index)
{
    char **cmd;
    char *path;

    cmd = ft_split(arg.v[cmd_index],' ');

    close(fd.pipe[0]); //???
    dup2(fd.tmp,STDIN_FILENO);
    close(fd.tmp);
    if (cmd_index + 1 < arg.c - 1)
        dup2(fd.pipe[1],STDOUT_FILENO);
    else
        dup2(fd.out,STDOUT_FILENO);
    close(fd.pipe[1]);
    path = fetch_pathname(cmd[0],arg.env);
    if ((execve(path, cmd, arg.env) == -1))
    {
        free(path);
        ft_exit_errno();
    }
}

t_arg   fetch_arg(char **argv, int argc, char **envp)
{
    t_arg arg;

    arg.v = argv;
    arg.c = argc;
    arg.env = envp;
    return (arg);
}


void  ft_exit_errno()
{
    strerror(errno);
    exit(EXIT_FAILURE);
}

t_fd open_file(char **argv, char argc)
{
    t_fd fd;

    fd.in = open(argv[1],O_RDONLY);
    if (fd.in == -1)
        ft_exit_errno();
    fd.out = open(argv[argc - 1],O_WRONLY | O_CREAT | O_TRUNC | O_RDONLY, 0777 );
    if (fd.out == -1)
        ft_exit_errno();
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
            ft_exit_errno();
        id = fork();
        if (id == -1)
            ft_exit_errno();
        if (id == 0)
            child_command(arg,fd, cmd_index);
        fd.tmp = fd.pipe[0];    
        close(fd.pipe[1]);
        cmd_index++;
    }
    return (0);
}