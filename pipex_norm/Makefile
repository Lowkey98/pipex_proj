NAME = pipex


SRC = main.c fetch_pathname.c ft_exit_errno.c

CC = gcc
FLAG = -Wall -Werror -Wextra
LIBFT_PATH = ../libft
all :$(NAME)

$(NAME): $(SRC)
			make -C $(LIBFT_PATH)
			$(CC) $(FLAG) $(SRC) -g $(LIBFT_PATH)/libft.a -o $(NAME)
clean:
			rm -f $(NAME)
fclean: clean
				make fclean -C $(LIBFT_PATH)
re: fclean all
