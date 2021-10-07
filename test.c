#include "libft/libft.h"

int main(int argc,char **argv)
{
	if(argc == 2)
		print_strings(ft_split(argv[1],' '));
}
