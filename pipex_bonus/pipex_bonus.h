#ifndef PIPEX_BONUS
# define PIPEX_BONUS
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_fd
{
    int pipe[2];
    int in;
    int out;
}   t_fd;
#endif