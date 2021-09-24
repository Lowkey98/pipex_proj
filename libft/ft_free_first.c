#include "libft.h"

char *ft_free_first(char *first, char *str)
{
    if (first == 0)
        return str;
    free(first);   
    return str;
}

void    ft_free_split(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}