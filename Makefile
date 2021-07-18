NAME = pipex

SRC = main.c read_file.c ft_strjoin.c

FLAG = gcc -Wall -Werror -Wextra

all :$(NAME)

$(NAME):
			$(FLAG) $(SRC) -o $(NAME)
clean:
			rm -f $(NAME)
fclean: clean

re: fclean all
