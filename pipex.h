#ifndef PIPEX
# define PIPEX
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

int     ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char    *read_file(char *filename);

#endif