#ifndef PIPEX
# define PIPEX
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
char    *read_file(char *filename);
void    exec_command(char *input, char **argv);

#endif