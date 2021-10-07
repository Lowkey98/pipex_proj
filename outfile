NAME = pipex


SRC = pipex_norm/main.c pipex_norm/fetch_pathname.c pipex_norm/ft_exit_errno.c

SRC_BONUS = pipex_bonus/fetch_pathname.c pipex_bonus/main.c
CC = gcc
FLAG = -Wall -Werror -Wextra
LIBFT_PATH = libft
all :$(NAME)

$(NAME): $(SRC)
			make -C $(LIBFT_PATH)
			$(CC) $(FLAG) $(SRC)  $(LIBFT_PATH)/libft.a -o $(NAME)
clean:
			rm -f $(NAME)
fclean: clean
				make fclean -C $(LIBFT_PATH)

bonus: fclean
		$(CC) $(FLAG) $(SRC_BONUS)  $(LIBFT_PATH)/libft.a -o $(NAME)

re: fclean all
