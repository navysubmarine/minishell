CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g3
NAME    = minishell

INCLUDE_DIRS = -Iincludes -Ift_printf/includes -Ilibft/includes -Imlx_linux/minilibx-linux

SOURCES = main.c 

OBJETS  = $(SOURCES:.c=.o)

FTPRINTF = includes/ft_printf/libftprintf.a
LIBFT    = includes/libft/libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJETS) $(FTPRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJETS) \
	-Llibft -lft \
	-Lft_printf -lftprintf \
	-o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(FTPRINTF):
	@$(MAKE) -C ft_printf

$(LIBFT):
	@$(MAKE) -C libft

clean:
	@$(MAKE) clean -C ft_printf
	@$(MAKE) clean -C libft
	rm -f $(OBJETS)

good: all clean

fclean: clean
	@$(MAKE) fclean -C ft_printf
	@$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all

