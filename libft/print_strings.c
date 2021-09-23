# include <stdio.h>

void print_strings(char **strings)
{
    int i = 0;
    while (strings[i])
    {
        printf("%s\n",strings[i]);
        i++;
    }
}