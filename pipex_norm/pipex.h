#ifndef PIPEX
# define PIPEX
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <string.h>
extern int errno ;

typedef struct s_fd
{
    int pipe[2];
    int in;
    int out;
}   t_fd;

typedef struct s_arg
{
    char **v;
    int c;
    char **env;
}   t_arg;
char    *read_file(char *filename);
char *fetch_pathname(char *cmd, char**envp);
void  ft_exit_errno(char *str);
#endif