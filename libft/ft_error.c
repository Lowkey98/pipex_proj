#  include "libft.h"

void    ft_error_msg(char *str)
{
    printf("%s\n",str);
    exit(EXIT_FAILURE);    
}

void    ft_error_two_msg(char *str_one, char *str_two)
{
    printf("%s %s\n",str_one, str_two);
    exit(EXIT_FAILURE);
}