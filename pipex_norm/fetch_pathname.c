# include "pipex.h"

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
        pathname = ft_strjoin_char(path[i],cmd,'/');
        if (access(pathname,F_OK) == 0)
            break;
        i++;
        free(pathname);
        if (path[i] == 0)
            ft_error_two_msg("zsh: command not found:",cmd);
    }
    ft_free_split(path);
    return pathname;
}