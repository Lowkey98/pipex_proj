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

void child_command(char **argv,int *pipe_fd, int fd_out, char **envp, int tmp_fd,int cmd_index, int argc)
{
    char **cmd;
    
    cmd = ft_split(argv[cmd_index],' ');

    close(pipe_fd[0]); //???
    dup2(tmp_fd,STDIN_FILENO);
    close(tmp_fd);
    if (cmd_index + 1 < argc - 1)
        dup2(pipe_fd[1],STDOUT_FILENO);
    else
        dup2(fd_out,STDOUT_FILENO);
    close(pipe_fd[1]);
    if ((execve(fetch_pathname(cmd[0],envp), cmd, envp) == -1))
        printf("error");
}

int main(int argc, char **argv,char **envp)
{
    t_fd fd;
    int id;
    int tmp_fd;
    int cmd_index = 2;
    if (argc == 1)
        return (0);
    fd.in = open(argv[1],O_RDONLY);
    fd.out = open(argv[argc - 1],O_WRONLY | O_CREAT | O_TRUNC | O_RDONLY, 0777 );
    tmp_fd = fd.in;
    while (cmd_index + 1 < argc)
    {

        if (pipe(fd.pipe) == -1)
            return (1);

        id = fork();
        if (id == 0)
        {
            //printf("a\n");
            child_command(argv, fd.pipe, fd.out, envp, tmp_fd, cmd_index,argc );
        }
        tmp_fd = fd.pipe[0];    
        //close(pipe_fd[0]);
        close(fd.pipe[1]);
        cmd_index++;
    }
    return (0);
}