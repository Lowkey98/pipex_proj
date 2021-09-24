# include  "pipex.h"

void  ft_exit_errno(char *str)
{
    if (!str)
        printf("Error: %s", strerror(errno));
    else
        printf("Error: %s: %s",strerror(errno),str);
    //printf("a");
    exit(EXIT_FAILURE);
}