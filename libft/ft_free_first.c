#include "libft.h"

char *ft_free_first(char *first, char *str)
{
    if (first == 0)
        return str;
    free(first);   
    return str;
}