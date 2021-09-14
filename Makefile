NAME = pipex


SRC = main.c read_file.c  exec_command.c

CC = gcc
FLAG = -Wall -Werror -Wextra
LIBFT = libft/libft.a
all :$(NAME)

$(NAME): $(SRC)
			make -C libft
			$(CC) $(FLAG) $(SRC) -g $(LIBFT) -o $(NAME)
clean:
			rm -f $(NAME)
fclean: clean
				make fclean -C libft
re: fclean all
