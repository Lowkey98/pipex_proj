NAME = pipex

SRC = main.c

FLAG = gcc -Wall -Werror -Wextra

all :$(NAME)

$(NAME):
			$(FLAG) $(SRC) -o $(NAME)
clean:
			rm -f $(NAME)
fclean: clean

re: fclean all
